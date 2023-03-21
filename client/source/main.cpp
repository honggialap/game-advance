#include "client.h"

int main() {
	//Client::GameClient game_client;
	//game_client.Run("data/game_data.json");

	Engine::Client client;
	if (client.Connect(Engine::IPEndPoint("::1",27015))) {
		while (client.IsConnecting()) {
			client.ProcessNetworks();
		}
		client.CleanUp();
	}

	system("pause");
	return 0;
}