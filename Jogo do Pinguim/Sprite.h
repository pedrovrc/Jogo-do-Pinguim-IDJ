#ifndef SPRITE_H
#define SPRITE_H

#include <bits/stdc++.h>
using namespace std;

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include "Rect.h"
#include "Component.h"

class Sprite : public Component{
	SDL_Texture* texture;
	int width;
	int height;
	SDL_Rect clipRect;
public:
	Sprite(GameObject& associated);
	Sprite(GameObject& associated, string file);
	~Sprite();
	void Open(string file);
	void SetClip(int x, int y, int w, int h);
	void Render();
	void Render(float x, float y, float w, float h);
	int GetWidth();
	int GetHeight();
	bool IsOpen();
	void Update(float dt);
	bool Is(string type);
};

#endif
