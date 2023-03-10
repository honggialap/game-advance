#include "game_server.h"
#include <Windows.h>

int main() {
	Server::GameServer game_server;
	game_server.Run();

	system("pause");
	return 0;
}