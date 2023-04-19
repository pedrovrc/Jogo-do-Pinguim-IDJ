#include "State.h"

State::State() {
	quitRequested = false;
	bg = *new Sprite("img/ocean.jpg");
	music.Open("audio/stageState.ogg");
	music.Play();
}

void State::LoadAssets() {
	// carregar imagens e musicas aqui quando possivel
}

void State::Update(float dt) {
	if (SDL_QuitRequested() == true) {
		quitRequested = true;
	}
}

void State::Render() {
	bg.Render();
}

bool State::QuitRequested() {
	return quitRequested;
}
