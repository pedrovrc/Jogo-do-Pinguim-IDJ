#include "Game.h"
#include "Resources.h"
Game* Game::instance;

#include "Camera.h"

/*
 * Game::Game(string title, int width, int height)
 *
 * Responsável por iniciar a classe e as diversas partes necessárias da biblioteca SDL.
 */
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
	frameStart = 0;
	dt = 0;
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

/*
 * Game& Game::GetInstance()
 *
 * Garante o padrão singleton nessa classe.
 */
Game& Game::GetInstance() {
	if (instance == nullptr) {
		instance = new Game(
			GAME_TITLE,
			WINDOW_WIDTH, WINDOW_HEIGHT
			);
	}
		return *instance;
}

/*
 * Game::CalculateDeltaTime()
 *
 * Responsável por consultar a biblioteca SDL e calcular o tempo entre frames (ms).
 */
void Game::CalculateDeltaTime() {
	int oldFrame = frameStart;
	frameStart = SDL_GetTicks();

	dt = 0.001*(frameStart - oldFrame);
}

/*
 * Game::Run()
 *
 * Responsável por executar o main game loop.
 */
void Game::Run() {
	state->Start();
	while(state->QuitRequested() == false) {
		CalculateDeltaTime();
		InputManager::GetInstance().Update();
		state->Update(dt);
		state->Render();
		SDL_RenderPresent(renderer);
		SDL_Delay(33);
	}
	Resources::ClearImages();
	Resources::ClearMusics();
	Resources::ClearSounds();
}

State& Game::GetState() {
	return *state;
}

SDL_Renderer* Game::GetRenderer() {
	return renderer;
}

float Game::GetDeltaTime() {
	return dt;
}
