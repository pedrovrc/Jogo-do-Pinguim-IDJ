#ifndef TILEMAP_H
#define TILEMAP_H

#include <bits/stdc++.h>
using namespace std;

#define TILE_WIDTH 64
#define TILE_HEIGHT 64

#include "Component.h"
#include "TileSet.h"

class TileMap : public Component {
	vector<int> tileMatrix;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;
public:
	TileMap(GameObject& associated, string file, TileSet* tileSet);
	void Load(string file);
	void SetTileSet(TileSet* tileSet);
	int& At(int x, int y, int z = 0);
	void Render();
	void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
	int GetWidth();
	int GetHeight();
	int GetDepth();
	void Update(float dt);
	bool Is(string type);
};

#endif
