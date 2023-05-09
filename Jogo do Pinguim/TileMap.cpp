#include "TileMap.h"

TileMap::TileMap(GameObject& associated, string file, TileSet* tileSet) : Component(associated) {
	Load(file);
	this->tileSet = new TileSet(64, 64, file);
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
			} else if (j == 1) {
				mapHeight = stoi(buffer);
			} else if (j == 2) {
				mapDepth = stoi(buffer);
			}
			j++;
			buffer.clear();
		}
	}

	// processa mapas
	// para cada camada existente
	for (int k = 0; k < mapDepth; k++) {

		// pula proxima linha (quebra de linha)
		getline(map, line);

		// para cada linha do mapa
		for (j = 0; j < mapHeight; j++) {

			// obtem linha
			getline(map, line);

			// obtem caracteres numericos e salva-os no vetor tileMatrix subtraido de 1
			while (i < line.length()) {
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
}

void TileMap::SetTileSet(TileSet* tileSet) {
	this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z = 0) {
	int xAcesso = x;
	int yAcesso = y * mapWidth;
	int zAcesso = z * mapWidth * mapHeight;
	int& access = tileMatrix[xAcesso + yAcesso + zAcesso];
	return access;
}

void TileMap::RenderLayer(int layer, int cameraX = 0, int cameraY = 0) {
	/*
	 * 	Renderiza uma camada do mapa, tile a tile. Note que há dois ajustes a
	 *	se fazer:
	 *	● Deve-se compensar o deslocamento da câmera
	 *	● Deve-se considerar o tamanho de cada tile (use os membros
	 *	GetTileWidth() e GetTileHeight() de TileSet)
	 *	Ainda não temos câmera. Você pode deixar para implementar o primeiro
	 *	ponto naquela ocasião, mas já faça a função recebendo esses argumentos.
	 */
}

void TileMap::Render() {
	for (int i = 0; i < mapDepth; i++) {
		RenderLayer(i, 0, 0);
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
