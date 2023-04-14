#include "State.h"

State::State() {
	this->quitRequested = false;
	this->bg = *new Sprite("img/ocean.jpg");
	this->music.Open("audio/stageState.ogg");
	this->music.Play();
}

void State::LoadAssets() {
	// carregar imagens e musicas aqui quando possivel
}

void State::Update(float dt) {
	if (SDL_QuitRequested() == true) {
		this->quitRequested = true;
	}
}

void State::Render() {
	this->bg.Render(0, 0);
}

bool State::QuitRequested() {
	return this->quitRequested;
}
