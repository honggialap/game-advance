#include "game.h"

int main() {
	Game server;
	server.Run("data/game_data.json");

	system("pause");
	return 0;
}