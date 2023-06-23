#include "State.h"
#include "Vec2.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "Collision.cpp"
#include "GeneralFunctions.h"
#include "Collider.h"

/*
 * State::State()
 *
 * Construtor que instancia assets da tela inicial e lista de GameObjects.
 */
State::State() {
	quitRequested = false;
	started = false;
}

State::~State() {
	while (objectArray.empty() == false) {
		objectArray.erase(objectArray.end() - 1);
	}
	objectArray.clear();
}

/*
 * State::LoadAssets()
 *
 * Responsável por carregar os assets iniciais de State.
 */
void State::LoadAssets() {
	// carregar imagens e musicas aqui quando possivel

	// cria GO ambient, atribui ele a Sprite do BG e ao CameraFollower
	GameObject* ambient = new GameObject;
	Component* bg = new Sprite(*ambient, "img/ocean.jpg", 1, 0);
	Component* follower = new CameraFollower(*ambient);
	ambient->AddComponent(bg);
	ambient->AddComponent(follower);
	ambient->box.MoveThis(*new Vec2(0,0));
	AddObject(ambient);

	// abre musica
	music.Open("audio/stageState.ogg");

	// criação do mapa
	GameObject* tileMapGO = new GameObject;
	TileSet* tileSet = new TileSet(TILE_WIDTH, TILE_HEIGHT, "img/tileset.png", *tileMapGO);
	Component* map = new TileMap(*tileMapGO, "map/tileMap.txt", tileSet);
	tileMapGO->AddComponent(map);
	tileMapGO->box.MoveThis(*new Vec2(0,0));
	AddObject(tileMapGO);

	// Adiciona Alien
	GameObject* AlienGO = new GameObject;
	Component* AlienCpt = new Alien(*AlienGO, 0);
	AlienGO->AddComponent(AlienCpt);
	AlienGO->box.MoveThis(*new Vec2(512,300));
	AddObject(AlienGO);

	// Adiciona Pinguim
	GameObject* penguinGO = new GameObject;
	AddObject(penguinGO);
	PenguinBody* penguin = new PenguinBody(*penguinGO);
	penguinGO->AddComponent((Component*)penguin);
	penguinGO->box.MoveThis(*new Vec2(704,640));
}

void State::Start() {
	LoadAssets();
	int i = 0;
	GameObject* go;
	while (objectArray.begin() + i != objectArray.end()) {
		go = (GameObject*)objectArray[i].get();
		go->Start();
		go->started = true;
		i++;
	}

	i = 0;
	Component* cpt = nullptr;
	GameObject* penguin = nullptr;
	while (objectArray.begin() + i != objectArray.end()) {
		go = (GameObject*)objectArray[i].get();
		cpt = go->GetComponent("PenguinBody");
		if (cpt != nullptr) {
			penguin = go;
			break;
		}
		i++;
	}
	if (penguin != nullptr) {
		Camera::Follow(penguin);
	} else {
		cout << "Erro ao encontrar GameObject do Player" << endl;
	}

	//music.Play();
	started = true;
}

/*
 * void State::Update(float dt)
 *
 * Chamado em todo frame, é responsável por atualizar todos os GameObjects gerenciados ou excluir objetos mortos.
 * Também é responsável por incluir face (inimigo) ao pressionar espaço.
 * Também cuida de atualizar o Input e a Câmera.
 */
void State::Update(float dt) {
	// atualiza input/quit
	InputManager* input = &(InputManager::GetInstance());
	quitRequested = input->QuitRequested();

	int size = objectArray.size(), i = 0;
	GameObject* go;
	Component* cpt = nullptr;
	GameObject* penguin = nullptr;
	while (objectArray.begin() + i != objectArray.end()) {
		go = (GameObject*)objectArray[i].get();
		cpt = go->GetComponent("PenguinBody");
		if (cpt != nullptr) {
			penguin = go;
			break;
		}
		i++;
	}

	// atualiza camera
	if (input->KeyPress(Y_KEY)) {
		if (Camera::following) Camera::Unfollow();
		else Camera::Follow(penguin);
	}

	Camera::Update(dt);

	// atualiza GameObjects
	i = 0;
	while (i < size) {
		go = (GameObject*)objectArray[i].get();
		go->Update(dt);
		i++;
	}

	// deteccao de colisao
	int j;
	cpt = nullptr;
	Component* cpt2 = nullptr;
	GameObject* go2;
	Collider* coll1;
	Collider* coll2;
	i = 0;
	while (i < size) {
		go = (GameObject*)objectArray[i].get();
		cpt = go->GetComponent("Collider");
		if (cpt != nullptr) {
			j = i+1;
			while (j < size) {
				go2 = (GameObject*)objectArray[j].get();
				cpt2 = go2->GetComponent("Collider");
				if (cpt2 != nullptr && cpt2 != cpt) {
					coll1 = (Collider*)cpt;
					coll2 = (Collider*)cpt2;
					if (Collision::IsColliding(coll1->box, coll2->box, Deg2Rad(go->angleDeg), Deg2Rad(go2->angleDeg))) {
						go->NotifyCollision(*go2);
						go2->NotifyCollision(*go);
					}
				}
				cpt2 = nullptr;
				j++;
			}
		}
		cpt = nullptr;
		i++;
	}

	// deleta GameObjects mortos
	i = 0;
	while (i < size) {
		go = (GameObject*)objectArray[i].get();
		if (go->IsDead()) {
			if (go->GetComponent("PenguinBody") != nullptr) Camera::Unfollow();
			DeleteObject(go);
			size--;
		}
		i++;
	}
}

/*
 * void State::Render()
 *
 * Responsável por renderizar todos os GameObjects gerenciados.
 */
void State::Render() {
	int i = 0;
	GameObject* go;
	while (objectArray.begin() + i != objectArray.end()) {
 		go = (GameObject*)objectArray[i].get();
		go->Render();
		i++;
	}

	// chamada extra de TileMap->Render para renderizar camadas acima
	i = 0;
	while (objectArray.begin() + i != objectArray.end()) {
		go = (GameObject*)objectArray[i].get();
		if (go->GetComponent("TileMap") != nullptr) {
			go->Render();
		}
		i++;
	}
}

/*
 * weak_ptr<GameObject> State::AddObject(GameObject* go)
 *
 * Adiciona novo GameObject à lista de GameObjects.
 */
weak_ptr<GameObject> State::AddObject(GameObject* go) {
	shared_ptr<GameObject> pointer(go);
	objectArray.push_back(pointer);
	if(started) pointer->Start();
	return weak_ptr<GameObject>(pointer);
}

/*
 * void State::DeleteObject(GameObject* go)
 *
 * Deleta um GameObject da lista.
 */
void State::DeleteObject(GameObject* go) {
	int size = objectArray.size(), i = 0;
	while (i < size) {
		if (go == (GameObject*)objectArray[i].get()) {
			objectArray.erase(objectArray.begin() + i);
			return;
		}
		i++;
	}
}

/*
 * weak_ptr<GameObject> State::GetObjectPtr(GameObject* go)
 *
 * Retorna um weak_ptr referenciando o go requisitado.
 */
weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
	int i = 0;
	while (objectArray.begin() + i != objectArray.end()) {
		if (objectArray[i].get() == go) return weak_ptr<GameObject>(objectArray[i]);
		i++;
	}
	return weak_ptr<GameObject>();
}

bool State::QuitRequested() {
	return quitRequested;
}
