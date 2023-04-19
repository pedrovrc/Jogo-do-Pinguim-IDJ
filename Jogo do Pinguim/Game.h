#ifndef GAME_H
#define GAME_H

#include <bits/stdc++.h>
using namespace std;

#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.h"

class Game {
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* state;
	Game(string title, int width, int height);
public:
	~Game();
	void Run();
	SDL_Renderer* GetRenderer();
	State& GetState();
	static Game& GetInstance();
};
#endif
