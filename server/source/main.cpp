#include "game_server.h"

int main() {
	Server::GameServer game_server;
	game_server.Run("data/game_data.json");

	system("pause");
	return 0;
}