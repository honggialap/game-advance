#include "server/core/game.h"

int main() {
	NSServer::NSCore::CGame game_server;
	game_server.Run("data/game_data.json");

	system("pause");
	return 0;
}