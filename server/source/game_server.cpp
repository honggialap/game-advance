#include "game_server.h"

namespace Server {

	void GameServer::Initialize() {
		unsigned int window_width = 800;
		unsigned int window_height = 600;
		std::string window_title = "Game Server";
		window.create(
			sf::VideoMode(window_width, window_height),
			window_title,
			sf::Style::Titlebar | sf::Style::Close
		);
		window.setFramerateLimit(0);

		float framerate = 60.0f;
		tick_per_frame = 1000.0f / framerate;
		elapsed_ms = 0.0f;

		Server::Initialize();

		printf("GameServer Initialize.\n");
	}

	void GameServer::Shutdown() {

		Server::Shutdown();

		printf("GameClient Shutdown.\n");
	}

	void GameServer::Run() {
		Initialize();

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

			ProcessListening();
			ProcessConnection();

			elapsed_ms += clock.GetMilliseconds();
			clock.Reset();

			if (elapsed_ms >= tick_per_frame) {
				Update(elapsed_ms);

				window.clear(sf::Color::Black);
				Render(window);
				window.display();

				elapsed_ms = 0.0f;
			}
			else {
				Sleep((DWORD)tick_per_frame - elapsed_ms);
			}
		}

		Shutdown();
	}

	void GameServer::Update(float elapsed_ms) {
	}

	void GameServer::Render(sf::RenderWindow& window) {
	}

	void GameServer::OnConnect(uint32_t connection_id) {
	}

	void GameServer::OnDisconnect(uint32_t connection_id) {
	}

	bool GameServer::ProcessPacket(std::shared_ptr<Engine::Packet> packet) {
		return false;
	}

}
