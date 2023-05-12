#include "Game.h"
#include "Resources.h"
Game* Game::instance;

Game::Game(string title, int width, int height) {
	if (instance != nullptr) {
		cout << "ERRO: Jogo ja esta em execucao" << endl;
		return;
	}
	instance = this;

	int error = 0;
	error = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
	if (error != 0) {
		cout << "Erro na inicializacao do SDL" << endl;
		cout << SDL_GetError() << endl;
		return;
	}

	error = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	if (error != (IMG_INIT_JPG | IMG_INIT_PNG)) {
		cout << "Erro na inicializacao do SDL_Image" << endl;
		cout << SDL_GetError() << endl;
		return;
	}

	error = Mix_Init(MIX_INIT_OGG);
	if (error != MIX_INIT_OGG) {
		cout << "Erro na inicializacao do SDL_Mixer" << endl;
		cout << SDL_GetError() << endl;
		return;
	}

	error = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	if (error != 0) {
		cout << "Erro na inicializacao do SDL_Mixer (OpenAudio)" << endl;
		cout << SDL_GetError() << endl;
		return;
	}

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if (window == nullptr) {
		cout << "Erro na inicializacao da janela (SDL_CreateWindow)" << endl;
		cout << SDL_GetError() << endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		cout << "Erro na inicializacao do renderizador (SDL_CreateRenderer)" << endl;
		cout << SDL_GetError() << endl;
		return;
	}

	state = new State;
}

Game::~Game() {
	free(state);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

Game& Game::GetInstance() {
	if (instance == nullptr) {
		instance = new Game(
			"Pedro Victor Rodrigues de Carvalho 170113043",
			1024, 600
			);
	}
		return *instance;
}

State& Game::GetState() {
	return *state;
}

SDL_Renderer* Game::GetRenderer() {
	return renderer;
}

void Game::Run() {
	while(state->QuitRequested() == false) {
		state->Update(0);
		state->Render();
		SDL_RenderPresent(renderer);
		SDL_Delay(33);
	}
	Resources::ClearImages();
	Resources::ClearMusics();
	Resources::ClearSounds();
}
