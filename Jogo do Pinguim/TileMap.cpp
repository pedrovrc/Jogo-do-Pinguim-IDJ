#include "TileMap.h"

TileMap::TileMap(GameObject& associated, string file, TileSet* tileSet) {
	Load(file);
	tileSet = new TileSet(64, 64, file);
}

void TileMap::Load(string file) {
	ifstream map;
	map.open("map/tileMap.txt");

	string line, buffer;
	int i = 0, j = 0;

	// processa primeira linha
	// parametros gerais do mapa
	getline(map, line);
	while (i < line.length()) {
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

	while () {
		getline(map, line);
		while (i < line.length()) {
			if (line[i] == ',') continue;

			buffer += line[i];

			if (line[i+1] == ',') {

				buffer.clear();
			}
		}
	}


}
