#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

/*
 * Sprite::Sprite()
 *
 * Responsável por iniciar o objeto sem um arquivo de imagem associado.
 */
Sprite::Sprite(GameObject& associated) : Component(associated) {
	texture = nullptr;
	height = 0;
	width = 0;
}

/*
 * Sprite::Sprite(GameObject& associated, string file)
 *
 * Responsável por iniciar o objeto já com a abertura de um arquivo de imagem.
 */
Sprite::Sprite(GameObject& associated, string file) : Component(associated) {
	texture = nullptr;
	Open(file);
	associated.box.h = height;
	associated.box.w = width;
}

Sprite::~Sprite() {

}

/*
 * void Sprite::Open(string file)
 *
 * Utiliza a classe Resources para abrir o arquivo de imagem requisitado.
 */
void Sprite::Open(string file) {
	texture = Resources::GetImage(file);

	if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0) {
		cout << "Erro 2 ao abrir imagem" << endl;
		cout << SDL_GetError() << endl;
		return;
	}

	SetClip(0, 0, width, height);
}

/*
 * void Sprite::SetClip(int x, int y, int w, int h)
 *
 * Seta o retângulo de corte (clipRect)
 */
void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

/*
 * void Sprite::Render()
 *
 * Chama o método de renderização com os parâmetros padrão de posição e tamanho (leva posição da câmera em consideração).
 */
void Sprite::Render() {
	Render(associated.box.x - Camera::pos.x, associated.box.y - Camera::pos.y, associated.box.w, associated.box.h);
}

/*
 * void Sprite::Render(float x, float y, float w, float h)
 *
 * Usa a biblioteca SDL para renderizar a textura (imagem) na tela dadas as coordenadas e dimensões passadas.
 */
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

void Sprite::Update(float dt) {

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

bool Sprite::Is(string type) {
	if (type == "Sprite") return true;
	return false;
}
