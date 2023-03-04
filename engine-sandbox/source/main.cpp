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
/*
int main() {
	const unsigned int window_width = 800;
	const unsigned int window_height = 600;
	const unsigned int framerate_limit = 144;

	sf::RenderWindow window(
		sf::VideoMode(window_width, window_height),
		"SFML Testing",
		sf::Style::Titlebar | sf::Style::Close
	);
	window.setFramerateLimit(framerate_limit);

	sf::Texture texture;
	if (!texture.loadFromFile(
		"data/test.png",
		sf::IntRect(0, 0, 64, 64))
		) {
	}
	texture.setSmooth(true);

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(100, 100);

	sf::Font font;
	if (!font.loadFromFile("data/arial.ttf")) {
	}

	sf::Text text;
	text.setFont(font);
	text.setString("TESTING FONT");
	text.setFillColor(sf::Color::Red);
	text.setPosition(200, 200);

	sf::View camera(
		sf::FloatRect(0, 0, 800, 600)
	);

	sf::SoundBuffer sfx_buffer;
	if (!sfx_buffer.loadFromFile("data/sfx.wav")) {
	}
	sf::Sound sfx;
	sfx.setBuffer(sfx_buffer);
	sfx.play();

	sf::Music music;
	if (!music.openFromFile("data/audio.wav")) {
	}

	while (window.isOpen()) {
		sf::Event window_event;
		while (window.pollEvent(window_event)) {
			switch (window_event.type) {
			case sf::Event::Closed: {
				window.close();
				break;
			}

			default:
				break;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			camera.move(0, -1.0f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			camera.move(0, 1.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			camera.move(-1.0f, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			camera.move(sf::Vector2f(1.0f, 0));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
			sfx.play();
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
			music.play();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
			music.stop();
		}

		window.setView(camera);
		window.clear(sf::Color::Black);
		window.draw(sprite);
		window.draw(text);

		window.display();
	}

	return 0;
}
*/