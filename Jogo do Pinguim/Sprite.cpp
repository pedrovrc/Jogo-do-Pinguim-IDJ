#include "Sprite.h"

Sprite::Sprite() {
	this->texture = nullptr;
	this->height = 0;
	this->width = 0;
	return;
}

Sprite::Sprite(string file) {
	this->texture = nullptr;
	this->Open(file);
	return;
}

Sprite::~Sprite() {
	if (this->IsOpen() == false) {
		SDL_DestroyTexture(this->texture);
	}
	return;
}

void Sprite::Open(string file) {
	if (this->IsOpen() == false) {
		SDL_DestroyTexture(this->texture);
	}
	Game& game = game.GetInstance();
	this->texture = IMG_LoadTexture(game.GetRenderer(), file.c_str());
	if (this->IsOpen() == false) {
		cout << "Erro ao abrir imagem" << endl;
		cout << SDL_GetError() << endl;
		return;
	}

	if (SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height) != 0) {
		cout << "Erro ao abrir imagem" << endl;
		cout << SDL_GetError() << endl;
		return;
	}

	this->SetClip(0, 0, this->width, this->height);
	return;
}

void Sprite::SetClip(int x, int y, int w, int h) {
	this->clipRect.x = x;
	this->clipRect.y = y;
	this->clipRect.w = w;
	this->clipRect.h = h;
	return;
}

void Sprite::Render(int x, int y) {
	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = this->clipRect.w;
	dstRect.h = this->clipRect.h;

	Game& game = game.GetInstance();
	if (SDL_RenderCopy(game.GetRenderer(), &this->texture, this->clipRect, dstRect) != 0) {
		cout << "Erro ao renderizar imagem" << endl;
		cout << SDL_GetError() << endl;
		return;
	}
}

int Sprite::GetWidth() {
	if (this->IsOpen() == false) {
		return -1;
	}
	return this->clipRect.w;
}

int Sprite::GetHeight() {
	if (this->IsOpen() == false) {
		return -1;
	}
	return this->clipRect.h;
}

bool Sprite::IsOpen() {
	if (this->texture == nullptr) {
		return false;
	} else {
		return true;
	}
}
