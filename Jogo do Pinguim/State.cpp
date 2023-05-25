#include "State.h"
#include "Face.h"
#include "Vec2.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Camera.h"
#include "CameraFollower.h"

/*
 * State::State()
 *
 * Construtor que instancia assets da tela inicial e lista de GameObjects.
 */
State::State() {
	quitRequested = false;

	// Cria GO ambient, atribui ele a Sprite do BG e ao CameraFollower
	GameObject* ambient = new GameObject;
	Component* bg = new Sprite(*ambient, "img/ocean.jpg");
	ambient->AddComponent(bg);
	Component* follower = new CameraFollower(*ambient);
	ambient->AddComponent(follower);

	// adiciona ambient a lista de GOs
	AddObject(ambient);

	music.Open("audio/stageState.ogg");
	music.Play();

	// criação do mapa
	GameObject* tileMapGO = new GameObject;
	TileSet* tileSet = new TileSet(TILE_WIDTH, TILE_HEIGHT, "img/tileset.png", *tileMapGO);
	Component* map = new TileMap(*tileMapGO, "map/tileMap.txt", tileSet);
	tileMapGO->AddComponent(map);
	tileMapGO->box.x = 0;
	tileMapGO->box.y = 0;

	// adiciona GO do mapa na lista de GOs
	AddObject(tileMapGO);
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
 * Responsável por carregar os assets.
 */
void State::LoadAssets() {
	// carregar imagens e musicas aqui quando possivel
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

	// add face
	if(input->KeyPress(SPACE_KEY)) {
		float angle = -M_PI + M_PI*(rand() % 1001)/500.0;	// angulo de rotacao randomizado
		float objX = input->GetMouseX() + Camera::pos.x;
		float objY = input->GetMouseY() + Camera::pos.y;
		Vec2 objPos = Vec2(200, 0).Rotate(angle) + Vec2(objX, objY);
		AddObjectKeyPress((int)objPos.x, (int)objPos.y);
	}

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
}

/*
 * void State::AddObjectKeyPress(int mouseX, int mouseY)
 *
 * Responsável por criar novo GameObject contendo a face (inimigo) nas coordenadas fornecidas.
 */
void State::AddObjectKeyPress(int mouseX, int mouseY) {
	GameObject* newGO = new GameObject;
	newGO->box.x = mouseX;
	newGO->box.y = mouseY;

	Sprite* enemy = new Sprite(*newGO, "img/penguinface.png");
	newGO->AddComponent(enemy);

	Sound* boom = new Sound(*newGO, "audio/boom.wav");
	newGO->AddComponent(boom);

	Face* penguinFace = new Face(*newGO);
	newGO->AddComponent(penguinFace);

	AddObject(newGO);
}

/*
 * void State::AddObject(GameObject* go)
 *
 * Adiciona novo GameObject à lista de GameObjects.
 */
void State::AddObject(GameObject* go) {
	objectArray.emplace_back(go);
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

bool State::QuitRequested() {
	return quitRequested;
}
