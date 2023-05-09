#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, string file){
	tileSet.Sprite(associated);
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	tileSet.Open(file);
	if (tileSet.IsOpen()) {
		rows = (tileSet.GetHeight()/tileHeight);
		columns = (tileSet.GetWidth()/tileWidth);
	} else {
		cout << "Erro ao carregar TileSet" << endl;
		SDL_GetError();
	}
}

void TileSet::RenderTile(unsigned index, float x, float y) {
	if (index >= 0 && index < (rows * columns)) {
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
