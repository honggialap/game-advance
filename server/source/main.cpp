#include "server.h"

int main() {
	//Server::GameServer game_server;
	//game_server.Run("data/game_data.json");

	Engine::Server server;
	if (server.Listen(Engine::IPEndPoint("::1", 27015))) {
		while (server.IsRunning()) {
			server.ProcessNetworks();
		}
		server.CleanUp();
	}

	system("pause");
	return 0;
}