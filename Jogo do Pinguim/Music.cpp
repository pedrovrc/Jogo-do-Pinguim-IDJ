#include "Music.h"

Music::Music() {
	this->music = nullptr;
	return;
}

Music::Music(string file) {
	this->music = nullptr;
	this->Open(file);
	return;
}

Music::~Music() {
	this->Stop();
	Mix_FreeMusic(this->music);
	return;
}

void Music::Play(int times) {
	if (this->IsOpen() == false) {
		cout << "Erro ao executar audio - Musica nao foi carregada" << endl;
		cout << SDL_GetError() << endl;
		return;
	}
	if (Mix_PlayMusic(this->music, times) == -1) {
		cout << "Erro ao executar audio" << endl;
		cout << SDL_GetError() << endl;
		return;
	}
	return;
}

void Music::Stop(int msToStop) {
	if (Mix_FadeOutMusic(msToStop) == 0) {
		cout << "Erro em Fade Out" << endl;
		cout << SDL_GetError() << endl;
		return;
	}
	return;
}

void Music::Open(string file) {
	this->music = Mix_LoadMUS(file.c_str());
	if (this->music == nullptr) {
		cout << "Erro ao carregar musica" << endl;
		cout << SDL_GetError() << endl;
		return;
	}
	return;
}

bool Music::IsOpen() {
	if (this->music == nullptr) {
		return false;
	} else {
		return true;
	}
}
