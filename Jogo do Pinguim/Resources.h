#ifndef RESOURCES_H
#define RESOURCES_H

#include <bits/stdc++.h>
using namespace std;

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

/*
 * Classe Resources
 *
 * Responsável por gerenciar os assets do jogo.
 */
class Resources {
	static unordered_map<string, SDL_Texture*> imageTable;
	static unordered_map<string, Mix_Music*> musicTable;
	static unordered_map<string, Mix_Chunk*> soundTable;
public:
	static SDL_Texture* GetImage(string file);
	static Mix_Music* GetMusic(string file);
	static Mix_Chunk* GetSound(string file);
	static void ClearImages();
	static void ClearMusics();
	static void ClearSounds();
};

#endif
