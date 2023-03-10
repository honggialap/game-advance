#include "game_client.h"
#include "lobby.h"
#include "world.h"

int main() {
	Client::GameClient game_client;
	game_client.Run("data/game_data.json");

	return 0;
}