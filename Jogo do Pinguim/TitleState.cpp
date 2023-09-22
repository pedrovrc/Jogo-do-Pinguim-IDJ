#include "TitleState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"
#include "Camera.h"
#include "Text.h"

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

	GameObject* go_text = new GameObject();
	SDL_Color white;
	white.r = 255;
	white.g = 255;
	white.b = 255;
	white.a = 255;
	Text* text = new Text(*go_text, "font/Call me maybe.ttf", 16, Text::SOLID, "Press SPACEBAR to start game", white);
	go_text->AddComponent((Component*) text);
	go_text->box.MoveThis(*new Vec2(300,80));
	go_text->box.w = 342;
	go_text->box.h = 80;
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
	return weak_ptr<GameObject>();
}
