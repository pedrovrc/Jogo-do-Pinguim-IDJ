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

class State {
	Sprite bg;
	Music music;
	bool quitRequested;
public:
	State();
	bool QuitRequested();
	void LoadAssets();
	void Update(float dt);
	void Render();
};
