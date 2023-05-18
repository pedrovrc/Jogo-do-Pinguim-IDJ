#include "State.h"
#include "Face.h"
#include "Vec2.h"
#include "TileMap.h"
#include "TileSet.h"

State::State() {
	quitRequested = false;

	// Cria GO ambient e atribui ele a Sprite do BG
	GameObject* ambient = new GameObject;
	Component* bg = new Sprite(*ambient, "img/ocean.jpg");
	ambient->AddComponent(bg);

	// adiciona ambient a lista de GOs
	AddObject(ambient);

	music.Open("audio/stageState.ogg");
	music.Play();

	// criação do mapa
	GameObject* tileMapGO = new GameObject;
	TileSet* tileSet = new TileSet(64, 64, "img/tileset.png", *tileMapGO);
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

void State::LoadAssets() {
	// carregar imagens e musicas aqui quando possivel
}

void State::Update(float dt) {
	InputManager* input = &(InputManager::GetInstance());
	quitRequested = input->QuitRequested();
	if(input->KeyPress(SPACE_KEY)) {
		Vec2 objPos = Vec2( 200, 0 ).Rotate( -M_PI + M_PI*(rand() % 1001)/500.0 ) + Vec2(float(input->GetMouseX()), float(input->GetMouseY()));
		AddObjectClick((int)objPos.x, (int)objPos.y);
	}

	int size = objectArray.size(), i = 0;
	GameObject* go;
	while (i < size) {
		go = (GameObject*)objectArray[i].get();
		go->Update(dt);
		i++;
	}

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

void State::Render() {
	int i = 0;
	GameObject* go;
	while (objectArray.begin() + i != objectArray.end()) {
 		go = (GameObject*)objectArray[i].get();
		go->Render();
		i++;
	}
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::AddObjectClick(int mouseX, int mouseY) {
	GameObject* newGO = new GameObject;

	// mudar para fazer x e y serem o centro do novo sprite
	newGO->box.x = mouseX;
	newGO->box.y = mouseY;

	Sprite* enemy = new Sprite(*newGO, "img/penguinface.png");
	newGO->AddComponent(enemy);

	Sound* boom = new Sound(*newGO, "audio/boom.wav");
	newGO->AddComponent(boom);

	Face* penguinFace = new Face(*newGO);
	newGO->AddComponent(penguinFace);

	objectArray.emplace_back(newGO);
}

void State::AddObject(GameObject* go) {
	objectArray.emplace_back(go);
}

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
