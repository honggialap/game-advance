#include "Game.h"

int main() {
	Game game;
	game.Run(
		sf::VideoMode(800, 600),
		"SFML Testing Game class",
		60
	);
	return 0;
}