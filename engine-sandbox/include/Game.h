#pragma once
#ifndef __PONG_GAME_H__
#define __PONG_GAME_H__

#include "Common.h"
#include "Scene.h"

class Game {
public:
	void Run(sf::VideoMode window_size, std::string window_title, unsigned int framerate_limit) {
		sf::RenderWindow window(
			window_size,
			window_title,
			sf::Style::Titlebar | sf::Style::Close
		);
		window.setFramerateLimit(framerate_limit);

		Scene scene;
		scene.Load();

		sf::Clock clock;
		clock.restart();

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

			scene.Update(clock.getElapsedTime().asMilliseconds());

			window.clear(sf::Color::Black);
			scene.Render(window);
			window.display();
		}
	}
};

#endif // !__PONG_GAME_H__
