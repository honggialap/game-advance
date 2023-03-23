#include "game_client.h"

int main() {
	Client::GameClient game_client;
	game_client.Run("data/game_data.json");

	system("pause");
	return 0;
}