#include "State.h"
#include "Vec2.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"

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
	Component* bg = new Sprite(*ambient, "img/ocean.jpg");
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
	cout << "adiciona alien" << endl;
	GameObject* AlienGO = new GameObject;
	Component* AlienCpt = new Alien(*AlienGO, 0);
	AlienGO->AddComponent(AlienCpt);
	AlienGO->box.MoveThis(*new Vec2(512,300));
	AddObject(AlienGO);
	cout << "adicionou" << endl;
}

void State::Start() {
	LoadAssets();
	int i = 0;
	GameObject* go;
	while (objectArray.begin() + i != objectArray.end()) {
		go = (GameObject*)objectArray[i].get();
		go->Start();
		i++;
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

	// atualiza camera
	Camera::Update(dt);

	// update GameObjects
	int size = objectArray.size(), i = 0;
	GameObject* go;
	while (i < size) {
		go = (GameObject*)objectArray[i].get();
		go->Update(dt);
		i++;
	}

	// deleta GameObjects mortos
	i = 0;
	while (i < size) {
		go = (GameObject*)objectArray[i].get();
		if (go->IsDead()) {
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
		if (objectArray[i] == shared_ptr<GameObject>(go)) return weak_ptr<GameObject>(objectArray[i]);
	}
	return weak_ptr<GameObject>();
}

bool State::QuitRequested() {
	return quitRequested;
}
