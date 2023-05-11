#include "Resources.h"
#include "Game.h"

unordered_map<string, SDL_Texture*> Resources::imageTable;
unordered_map<string, Mix_Music*> Resources::musicTable;
unordered_map<string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(string file) {
	auto it = imageTable.find(file);
	SDL_Texture* reference = it->second;
	// se encontrar imagem na tabela
	if (it != imageTable.end()) {
		return reference;
	} else {
		Game& game = game.GetInstance();
		reference = IMG_LoadTexture(game.GetRenderer(), file.c_str());
		if (reference == nullptr) {
			cout << "Erro 1 ao abrir imagem" << endl;
			cout << SDL_GetError() << endl;
			return nullptr;
		}

		imageTable.emplace(file, reference);
		return reference;
	}
}

Mix_Music* Resources::GetMusic(string file) {
	auto it = musicTable.find(file);
	Mix_Music* reference = it->second;
	if (it != musicTable.end()) {
		return reference;
	} else {
		reference = Mix_LoadMUS(file.c_str());
		if (reference == nullptr) {
			cout << "Erro ao carregar musica" << endl;
			cout << SDL_GetError() << endl;
			return nullptr;
		}
		musicTable.emplace(file, reference);
		return reference;
	}
}

Mix_Chunk* Resources::GetSound(string file) {
	auto it = soundTable.find(file);
	Mix_Chunk* reference = it->second;
	if (it != soundTable.end()) {
		return reference;
	} else {
		reference = Mix_LoadWAV(file.c_str());
		if (reference == nullptr) {
			cout << "Erro ao carregar musica" << endl;
			cout << SDL_GetError() << endl;
			return nullptr;
		}
		soundTable.emplace(file, reference);
		return reference;
	}
}

void Resources::ClearImages() {
	SDL_Texture* pointer;
	for (auto& it : imageTable) {
		pointer = it.second;
		SDL_DestroyTexture(pointer);
	}
	imageTable.clear();
}

void Resources::ClearMusics() {
	Mix_Music* pointer;
	for (auto& it : musicTable) {
		pointer = it.second;
		Mix_FreeMusic(pointer);
	}
	musicTable.clear();
}

void Resources::ClearSounds() {
	Mix_Chunk* pointer;
	for (auto& it : soundTable) {
		pointer = it.second;
		Mix_FreeChunk(pointer);
	}
	soundTable.clear();
}
