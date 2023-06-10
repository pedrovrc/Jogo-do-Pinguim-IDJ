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
	frameWidth = 0;
	SetFrameCount(1);
	SetFrame(0);
	timeElapsed = 0;
	SetFrameTime(0);
	scale.Set(1,1);
	SetClip(0,0,0,0);
}

/*
 * Sprite::Sprite(GameObject& associated, string file)
 *
 * Responsável por iniciar o objeto já com a abertura de um arquivo de imagem.
 */
Sprite::Sprite( GameObject& associated,
				string file,
				int frameCount,
				int frameTime ) : Component(associated) {
	texture = nullptr;
	Open(file);
	scale.Set(1,1);
	SetFrameCount(frameCount);
	frameWidth = width/frameCount;
	SetFrameTime(frameTime);
	SetFrame(0);
	associated.box.SetDimensions(frameWidth, height);
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
 * void Sprite::SetScale(float scaleX, float scaleY)
 *
 * Seta a escala do sprite. Se qualquer dos parâmetros fornecidos for zero, não muda o atual.
 */
void Sprite::SetScale(float scaleX, float scaleY) {
	if (scaleX == 0) scaleX = scale.x;
	if (scaleY == 0) scaleY = scale.y;
	scale.Set(scaleX, scaleY);
	Vec2 center = associated.box.GetCenter();
	associated.box.SetDimensions(frameWidth * scaleX, height * scaleY);
	associated.box.SetCenterPosition(center);
}

/*
 * void Sprite::Render()
 *
 * Chama o método de renderização com os parâmetros padrão de posição e tamanho (leva posição da câmera em consideração).
 */
void Sprite::Render() {
	Render( associated.box.x - Camera::pos.x,
			associated.box.y - Camera::pos.y,
			associated.box.w,
			associated.box.h );
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
	if (SDL_RenderCopyEx( game.GetRenderer(),
			 	 	 	  texture,
						  &clipRect,
						  &dstRect,
						  associated.angleDeg,
						  nullptr,
						  SDL_FLIP_NONE ) != 0 ) {
		cout << "Erro ao renderizar imagem" << endl;
		cout << SDL_GetError() << endl;
		return;
	}
}

void Sprite::Start() {

}

/*
 * void Sprite::Update(float dt)
 *
 * Checa se o tempo passado ultrapassa o tempo por frame de animação.
 * Se tiver passado, reseta o contador e passa para o próximo frame.
 * Se frameTime for zero ou frameCount for 1, não faz nada.
 */
void Sprite::Update(float dt) {
	if (frameCount == 1) return;

	timeElapsed += Game::GetInstance().GetDeltaTime();
	if (timeElapsed >= frameTime) {
		timeElapsed = 0;
		if (currentFrame + 1 == frameCount) {
			SetFrame(0);
		} else {
			SetFrame(currentFrame + 1);
		}
	}
}

void Sprite::SetFrame(int frame) {
	currentFrame = frame;
	SetClip(currentFrame * width, 0, frameWidth, height);
}

void Sprite::SetFrameCount(int frameCount) {
	this->frameCount = frameCount;
}

void Sprite::SetFrameTime(float frameTime) {
	this->frameTime = frameTime;
}


int Sprite::GetWidth() {
	if (IsOpen() == false) {
		return -1;
	}
	return frameWidth * scale.x;
}

int Sprite::GetHeight() {
	if (this->IsOpen() == false) {
		return -1;
	}
	return height * scale.y;
}

Vec2 Sprite::GetScale() {
	return scale;
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
