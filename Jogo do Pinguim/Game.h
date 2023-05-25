#ifndef GAME_H
#define GAME_H

#include <bits/stdc++.h>
using namespace std;

#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.h"
#include "InputManager.h"

/*
 * Classe Game
 *
 * Segue o padrão singleton, instanciada na função main e responsável por executar o jogo.
 */
class Game {
	int frameStart;
	float dt;
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* state;
	Game(string title, int width, int height);
	void CalculateDeltaTime();
public:
	~Game();
	void Run();
	SDL_Renderer* GetRenderer();
	State& GetState();
	static Game& GetInstance();
	float GetDeltaTime();
};
#endif
