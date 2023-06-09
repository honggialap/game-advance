#include "client/core/game.h"

int main() {
	NSClient::NSCore::CGame game_client;
	game_client.Run("data/game_data.json");

	system("pause");
	return 0;
}