#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, string file) {
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	tileSet.Open(file);
	rows = tileSet.GetHeight();
	columns = tileSet.GetWidth();
}

void TileSet::RenderTile(unsigned index, float x, float y) {
	if (0 <= index && index <= (rows * columns)-1) {
		tileSet.SetClip(x, y, tileWidth, tileHeight);
		tileSet.Render(x, y, tileWidth, tileHeight);
	}
}

int TileSet::GetTileWidth() {
	return tileWidth;
}

int TileSet::GetTileHeight() {
	return tileHeight;
}
