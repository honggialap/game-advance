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
		window.setFramerateLimit(0);
		float tick_per_frame = 1000.0f / framerate_limit;
		float elapsedMs = 0.0f;

		Scene scene;
		scene.Load();

		b2Timer clock;

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

			elapsedMs += clock.GetMilliseconds();
			clock.Reset();

			if (elapsedMs >= tick_per_frame) {
				scene.Update(elapsedMs);

				window.clear(sf::Color::Black);
				scene.Render(window);
				window.display();

				elapsedMs = 0.0f;
			}
			else {
				Sleep((DWORD)tick_per_frame - elapsedMs);
			}

		}
	}
};

#endif // !__PONG_GAME_H__
