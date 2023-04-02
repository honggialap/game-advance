#include "game.h"

int main() {
	Game client;
	client.Run("data/game_data.json");

	system("pause");
	return 0;
}