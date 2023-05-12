#include "Sprite.h"
#include "Game.h"
#include "Resources.h"

Sprite::Sprite(GameObject& associated) : Component(associated) {
	texture = nullptr;
	height = 0;
	width = 0;
}

Sprite::Sprite(GameObject& associated, string file) : Component(associated) {
	cout << "Sprite::Sprite() start" << endl;
	texture = nullptr;
	cout << "Sprite::Sprite() open" << endl;
	Open(file);
	associated.box.h = height;
	associated.box.w = width;
	cout << "Sprite::Sprite() end" << endl;
}

Sprite::~Sprite() {

}

void Sprite::Open(string file) {
	cout << "Sprite::Open() start" << endl;
	texture = Resources::GetImage(file);

	cout << "Sprite::Open() after GetImage()" << endl;

	if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0) {
		cout << "Erro 2 ao abrir imagem" << endl;
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
	Render(associated.box.x, associated.box.y, associated.box.w, associated.box.h);
}

void Sprite::Render(float x, float y, float w, float h) {
	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = w;
	dstRect.h = h;

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
