#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
using namespace std;

#define INCLUDE_SDL

#ifdef INCLUDE_SDL
	#ifdef _WIN32
		#include <SDL2/SDL.h>
	#elif __APPLE__
		#include "TargetConditionals.h"
		#include <SDL2/SDL.h>
	#elif __linux__
		#include <SDL2/SDL.h>
	#else
		#error "Unknown compiler"
	#endif
	#undef INCLUDE_SDL
#endif // INCLUDE_SDL

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
