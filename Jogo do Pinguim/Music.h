#ifndef MUSIC_H
#define MUSIC_H

#include <iostream>
#include <string>
using namespace std;

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

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
