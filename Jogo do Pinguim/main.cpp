#include "Game.h"

/*
 * 	main()
 * 	Função principal, responsável por dar início à execução do jogo.
 */
int main(int argc, char** argv) {
	Game& game = game.GetInstance();
	game.Run();
	return 0;
}
