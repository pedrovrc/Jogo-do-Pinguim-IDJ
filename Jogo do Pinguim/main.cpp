#include "Game.h"

int main(int argc, char** argv) {
	cout << "start" << endl;
	Game& game = game.GetInstance();
	cout << "Game.Run()" << endl;
	game.Run();
	cout << "end" << endl;
	return 0;
}
