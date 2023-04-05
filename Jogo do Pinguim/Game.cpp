#include "Game.h"

#ifdef INCLUDE_SDL_IMAGE
	#ifdef _WIN32
		#include <SDL2/SDL_image.h>
	#elif __APPLE__
		#include "TargetConditionals.h"
		#include <SDL2/SDL_image.h>
	#elif __linux__
		#include <SDL2/SDL_image.h>
	#else
		#error "Unknown compiler"
	#endif
	#undef INCLUDE_SDL_IMAGE
#endif // INCLUDE_SDL_IMAGE

#ifdef INCLUDE_SDL_MIXER
	#ifdef _WIN32
		#include <SDL2/SDL_mixer.h>
	#elif __APPLE__
		#include "TargetConditionals.h"
		#include <SDL2/SDL_mixer.h>
	#elif __linux__
		#include <SDL2/SDL_mixer.h>
	#else
		#error "Unknown compiler"
	#endif
	#undef INCLUDE_SDL_MIXER
#endif // INCLUDE_SDL_MIXER

// Classe Game
class Game {
	string title;
	int width;
	int height;
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* state;
	void Game(string title, int width, int height) {
		if (instance != nullptr) {
			cout << "ERRO: Jogo ja esta em execucao" << endl;
			return;
		}
		instance = this;
		return;
	}
public:
	void ~Game();
	void Run();
	SDL_Renderer* GetRenderer();
	State& GetState();
	static Game& GetInstance() {
		if (instance == nullptr) {
				instance = new Game;
			}
			return *instance;
	}
};








