#include "Sound.h"

Sound::Sound(GameObject& associated) {
	chunk = nullptr;
	this->associated = associated;
	channel = 0;
}

Sound::Sound(GameObject& associated, string file) {
	Sound(associated);
	Open(file);
}

Sound::~Sound() {
	if (IsOpen() == false) return;
	Mix_HaltChannel(channel);
	Mix_FreeChunk(chunk);
}

void Sound::Play(int times = 1) {
	channel = Mix_PlayChannel(-1, chunk, times-1);
}

void Sound::Stop() {
	if (IsOpen() == false) return;
	Mix_HaltChannel(channel);
}

void Sound::Open(string file) {
	chunk = Mix_LoadWAV(file.c_str());
	if (IsOpen() == false) {
		cout << "Erro ao carregar wav" << endl;
		SDL_GetError();
	}
}

bool Sound::IsOpen() {
	if (chunk == nullptr) return false;
	return true;
}

void Sound::Update(float dt) {

}

void Sound::Render() {

}

bool Sound::Is(string type) {
	if (type == "Sound") return true;
	return false;
}
