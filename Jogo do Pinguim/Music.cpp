#include "Music.h"
#include "Resources.h"

Music::Music() {
	music = nullptr;
}

Music::Music(string file) {
	music = nullptr;
	Open(file);
}

Music::~Music() {
	Stop();
}

void Music::Play(int times) {
	if (this->IsOpen() == false) {
		cout << "Erro ao executar audio - Musica nao foi carregada" << endl;
		cout << SDL_GetError() << endl;
		return;
	}
	if (Mix_PlayMusic(music, times) == -1) {
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
	music = Resources::GetMusic(file);
}

bool Music::IsOpen() {
	if (music == nullptr) {
		return false;
	} else {
		return true;
	}
}
