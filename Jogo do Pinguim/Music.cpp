#include "Music.h"

Music::Music() {
	this->music = nullptr;
}

Music::Music(string file) {
	this->music = nullptr;
	this->Open(file);
}

Music::~Music() {
	this->Stop();
	Mix_FreeMusic(this->music);
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
}

void Music::Stop(int msToStop) {
	if (Mix_FadeOutMusic(msToStop) == 0) {
		cout << "Erro em Fade Out" << endl;
		cout << SDL_GetError() << endl;
		return;
	}
}

void Music::Open(string file) {
	this->music = Mix_LoadMUS(file.c_str());
	if (this->music == nullptr) {
		cout << "Erro ao carregar musica" << endl;
		cout << SDL_GetError() << endl;
		return;
	}
}

bool Music::IsOpen() {
	if (this->music == nullptr) {
		return false;
	} else {
		return true;
	}
}
