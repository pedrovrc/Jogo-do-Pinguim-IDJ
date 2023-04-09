#include "Sprite.h"

#define INCLUDE_SDL_IMAGE
#ifdef INCLUDE_SDL_IMAGE
	#ifdef _WIN32
		#include <SDL2/SDL_image.h>
	#elif __APPLE__
		#include "TargetConditionals.h"
		#include <SDL2/SDL_image.h>
	#elif __linux__
		#include <SDL2/SDL_image.h>
	#else
		#error "Unknown compiler"
	#endif
	#undef INCLUDE_SDL_IMAGE
#endif // INCLUDE_SDL_IMAGE

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
	if (this->texture != nullptr) {
		SDL_DestroyTexture(this->texture);
	}
	return;
}

void Sprite::Open(string file) {
	if (this->texture != nullptr) {
		SDL_DestroyTexture(this->texture);
	}
	if (IMG_LoadTexture(renderer, file.c_str()) == nullptr) {	// passar renderer da Game
		cout << "Erro ao abrir imagem" << endl;
		cout << SDL_GetError() << endl;
		return;
	}
}
