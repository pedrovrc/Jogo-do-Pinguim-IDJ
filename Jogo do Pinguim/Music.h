#ifndef MUSIC_H
#define MUSIC_H

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

#define INCLUDE_SDL_MIXER
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

class Music {
	Mix_Music* music;
public:
	Music();
	Music(string file);
	~Music();
	void Play(int times = -1);
	void Stop(int msToStop = 1500);
	void Open (string file);
	bool IsOpen();
};

#endif
