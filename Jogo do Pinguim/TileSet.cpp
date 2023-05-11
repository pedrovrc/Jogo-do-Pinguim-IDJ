#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, string file, GameObject& associated) : tileSet(associated, file){
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	if (tileSet.IsOpen()) {
		rows = (tileSet.GetHeight()/tileHeight);
		columns = (tileSet.GetWidth()/tileWidth);
	} else {
		cout << "Erro ao carregar TileSet" << endl;
		SDL_GetError();
	}
}

void TileSet::RenderTile(unsigned index, float x, float y) {
	if (index < unsigned(rows * columns)) {
		tileSet.SetClip((index%columns) * tileWidth, (index/columns) * tileHeight, tileWidth, tileHeight);
		tileSet.Render(x, y, tileWidth, tileHeight);
	}
}

int TileSet::GetTileWidth() {
	return tileWidth;
}

int TileSet::GetTileHeight() {
	return tileHeight;
}
