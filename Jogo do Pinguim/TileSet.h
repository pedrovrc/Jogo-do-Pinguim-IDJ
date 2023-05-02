#ifndef SOUND_H
#define SOUND_H

#include <bits/stdc++.h>
using namespace std;

#include "Sprite.h"

class TileSet {
	Sprite tileSet;
	int rows;
	int columns;
	int tileWidth = 0;
	int tileHeight = 0;
public:
	TileSet(int tileWidth, int tileHeight, string file);
	void RenderTile(unsigned index, float x, float y);
	int GetTileWidth();
	int GetTileHeight();
};

#endif
