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

#include <iostream>
#include <string>

class Game {
	string title;
	int width;
	int height;
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* state;
	void Game(string title, int width, int height);
public:
	void ~Game();
	void Run();
	SDL_Renderer* GetRenderer();
	State& GetState();
	static Game& GetInstance();
};
