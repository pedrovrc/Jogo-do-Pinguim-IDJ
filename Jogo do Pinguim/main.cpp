#include "Game.h"
#include "StageState.h"

/*
 * 	main()
 * 	Função principal, responsável por dar início à execução do jogo.
 */
int main(int argc, char** argv) {
	Game& game = game.GetInstance();
	State* state = (State*) new StageState();
	game.Push(state);
	game.Run();
	return 0;
}
