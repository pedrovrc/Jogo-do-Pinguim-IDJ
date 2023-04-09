#include "State.h"

State::State() {
	this->quitRequested = false;
	this->bg = new Sprite;
	return;
}

void State::LoadAssets() {
	// carregar imagens e musicas aqui quando possivel
}

void State::Update(float dt) {
	if (SDL_QuitRequested() == true) {
		this->quitRequested = true;
	}
	return;
}

void State::Render() {
	// chamar render do fundo (bg)
}

bool State::QuitRequested() {
	return this->quitRequested;
}
