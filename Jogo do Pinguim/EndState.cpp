#include "EndState.h"
#include "Game.h"
#include "Sprite.h"
#include "Music.h"
#include "Text.h"

EndState::EndState() {
	Game& game = game.GetInstance();
	if (game.gameData.playerVictory) {
		// vitoria
		// carrega bg
		GameObject* go_bg = new GameObject();
		Component* bg = new Sprite(*go_bg, "img/win.jpg", 1, 0);
		go_bg->AddComponent(bg);
		go_bg->box.MoveThis(*new Vec2(0,0));
		AddObject(go_bg);

		// carrega musica
		backgroundMusic.Open("audio/endStateWin.ogg");
	} else {
		// derrota
		// carrega bg
		GameObject* go_bg = new GameObject();
		Component* bg = new Sprite(*go_bg, "img/lose.jpg", 1, 0);
		go_bg->AddComponent(bg);
		go_bg->box.MoveThis(*new Vec2(0,0));
		AddObject(go_bg);

		// carrega musica
		backgroundMusic.Open("audio/endStateLose.ogg");
	}

	GameObject* go_text = new GameObject();
	SDL_Color black;
	black.r = 0;
	black.g = 0;
	black.b = 0;
	black.a = 255;
	Text* text = new Text(*go_text,
						  "font/Call me maybe.ttf", 16,
						  Text::TextStyle::SOLID,
						  "Press ESC to exit\nPress SPACEBAR to play again",
						  black, 0.5);
	go_text->AddComponent((Component*) text);
	go_text->box.SetCenterPosition(*new Vec2(400,500));
	go_text->box.w = 500;
	go_text->box.h = 100;
	AddObject(go_text);
}

EndState::~EndState() {

}

void EndState::LoadAssets() {

}

void EndState::Update(float dt) {
	UpdateArray(dt);
	InputManager* input = &(InputManager::GetInstance());
	quitRequested = input->QuitRequested();

	if (input->KeyPress(SPACE_KEY)) {
		quitRequested = true;
	}
}

void EndState::Render() {

}

void EndState::Start() {
	backgroundMusic.Play();
}

void EndState::Pause() {

}

void EndState::Resume() {

}

/*
 * 	weak_ptr<GameObject> StageState::GetPlayerGO()
 *
 * 	Retorna weak_ptr apontando para o GO do player.
 */
weak_ptr<GameObject> EndState::GetPlayerGO() {
	int i = 0;
	while (objectArray.begin() + i != objectArray.end()) {
		if (objectArray[i].get()->GetComponent("PenguinBody") != nullptr) return weak_ptr<GameObject>(objectArray[i]);
		i++;
	}
	return weak_ptr<GameObject>();
}


