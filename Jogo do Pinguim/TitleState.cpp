#include "TitleState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"
#include "Camera.h"

TitleState::TitleState() {

}

TitleState::~TitleState() {

}

void TitleState::Update(float dt) {
	InputManager* input = &(InputManager::GetInstance());
	quitRequested = input->QuitRequested();

	if (input->KeyPress(SPACE_KEY)) {
		Game& game = game.GetInstance();
		State* state = (State*) new StageState();
		game.Push(state);
	}
}

void TitleState::LoadAssets() {
	GameObject* go = new GameObject();
	Component* bg = new Sprite(*go, "img/title.jpg", 1, 0);
	go->AddComponent(bg);
	go->box.MoveThis(*new Vec2(0,0));
	AddObject(go);
}

void TitleState::Render() {
	RenderArray();
}

void TitleState::Start() {
	LoadAssets();
}

void TitleState::Pause() {

}

void TitleState::Resume() {
	Camera::pos = *new Vec2(0,0);
}

weak_ptr<GameObject> TitleState::GetPlayerGO() {

}