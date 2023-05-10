#include "TileMap.h"

TileMap::TileMap(GameObject& associated, string file, TileSet* tileSet) : Component(associated) {
	Load(file);
	this->tileSet = new TileSet(64, 64, file, associated);
}

void TileMap::Load(string file) {
	ifstream map;
	map.open("map/tileMap.txt");

	string line, buffer;
	int i = 0, j = 0;

	// processa primeira linha
	// parametros gerais do mapa
	getline(map, line);
	for (i = 0; i < line.length(); i++) {
		if (line[i] == ',') continue;

		buffer += line[i];

		if (line[i+1] == ',') {
			if (j == 0) {
				mapWidth = stoi(buffer);
				cout << "mapWidth = " << stoi(buffer) << endl;
			} else if (j == 1) {
				mapHeight = stoi(buffer);
				cout << "mapHeight = " << stoi(buffer) << endl;
			} else if (j == 2) {
				mapDepth = stoi(buffer);
				cout << "mapDepth = " << stoi(buffer) << endl;
			}
			j++;
			buffer.clear();
		}
	}
	bool flagDebug = false;

	// processa mapas
	// para cada camada existente
	for (int k = 0; k < mapDepth; k++) {

		// pula proxima linha (quebra de linha)
		getline(map, line);

		// para cada linha do mapa
		for (j = 0; j < mapHeight; j++) {

			// obtem linha
			getline(map, line);

			flagDebug = true;
			// obtem caracteres numericos e salva-os no vetor tileMatrix subtraido de 1
			for (i = 0; i < line.length(); i++) {

				if (flagDebug) {
					cout << "[i, j, k] = " << i << j << k << endl;
					flagDebug = false;
				}

				if (line[i] == ',') continue;

				// salva caracter numerico em buffer
				buffer += line[i];

				// se esse for o ultimo numero em sequencia, salva no tileMatrix subtraido de 1
				if (line[i+1] == ',') {
					tileMatrix.push_back(stoi(buffer) - 1);
					buffer.clear();
				}
			}
		}
	}
	cout << "Terminou de ler mapa" << endl;
}

void TileMap::SetTileSet(TileSet* tileSet) {
	this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {
	int xAcesso = x;
	int yAcesso = y * mapWidth;
	int zAcesso = z * mapWidth * mapHeight;
	int& access = tileMatrix[xAcesso + yAcesso + zAcesso];
	return access;
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
	int index = 0;
	float x = 0, y = 0;
	int widthOffset = tileSet->GetTileWidth();
	int heightOffset = tileSet->GetTileHeight();
	for (int i = 0; i < mapWidth; i++) {
		for (int j = 0; i < mapHeight; i++) {
			for (int k = 0; i < mapDepth; i++) {
				index = At(i, j, k);
				x =	i * widthOffset;
				y = j * heightOffset;
				tileSet->RenderTile(index, x + cameraX, y + cameraY);
			}
		}
	}
}

void TileMap::Render() {
	for (int i = 0; i < mapDepth; i++) {
		RenderLayer(i, 0, 0);
		cout << "RenderLayer" << i << endl;
	}
}

int TileMap::GetWidth() {
	return mapWidth;
}

int TileMap::GetHeight() {
	return mapHeight;
}

int TileMap::GetDepth() {
	return mapDepth;
}

void TileMap::Update(float dt) {

}

bool TileMap::Is(string type) {
	if (type == "TileMap") return true;
	return false;
}
