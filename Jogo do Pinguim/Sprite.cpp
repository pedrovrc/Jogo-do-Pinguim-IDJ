#include "Sprite.h"
#include "Game.h"

Sprite::Sprite() {
	texture = nullptr;
	height = 0;
	width = 0;
}

Sprite::Sprite(string file) {
	texture = nullptr;
	Open(file);
	associated.box.h = height;
	associated.box.w = width;
}

Sprite::~Sprite() {
	if (IsOpen() == false) {
		SDL_DestroyTexture(texture);
	}
}

void Sprite::Open(string file) {
	if (IsOpen() == false) {
		SDL_DestroyTexture(texture);
	}
	Game& game = game.GetInstance();
	texture = IMG_LoadTexture(game.GetRenderer(), file.c_str());
	if (IsOpen() == false) {
		cout << "Erro ao abrir imagem" << endl;
		cout << SDL_GetError() << endl;
		return;
	}

	if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0) {
		cout << "Erro ao abrir imagem" << endl;
		cout << SDL_GetError() << endl;
		return;
	}

	SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render() {
	SDL_Rect dstRect;
	dstRect.x = associated.box.x;
	dstRect.y = associated.box.y;
	dstRect.w = associated.box.w;
	dstRect.h = associated.box.h;

	Game& game = game.GetInstance();
	if (SDL_RenderCopy(game.GetRenderer(), texture, &clipRect, &dstRect) != 0) {
		cout << "Erro ao renderizar imagem" << endl;
		cout << SDL_GetError() << endl;
		return;
	}
}

int Sprite::GetWidth() {
	if (IsOpen() == false) {
		return -1;
	}
	return width;
}

int Sprite::GetHeight() {
	if (this->IsOpen() == false) {
		return -1;
	}
	return height;
}

bool Sprite::IsOpen() {
	if (this->texture == nullptr) {
		return false;
	} else {
		return true;
	}
}

void Sprite::Update(float dt) {

}

bool Sprite::Is(string type) {
	if (type == "Sprite") return true;
	return false;
}
