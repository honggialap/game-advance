#include "game_client.h"
#include "lobby.h"
#include "world.h"

namespace Client {

	void GameClient::Initialize() {
		unsigned int window_width = 800;
		unsigned int window_height = 600;
		std::string window_title = "Game Client";
		window.create(
			sf::VideoMode(window_width, window_height),
			window_title,
			sf::Style::Titlebar | sf::Style::Close
		);
		window.setFramerateLimit(0);

		float framerate = 60.0f;
		tick_per_frame = 1000.0f / framerate;
		elapsed_ms = 0.0f;

		Client::Initialize();

		printf("GameClient Initialize.\n");
		return;
	}

	void GameClient::Shutdown() {
		Client::Shutdown();

		printf("GameClient Shutdown.\n");
		return;
	}

	void GameClient::Run() {
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

			ProcessNetworks();

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

	void GameClient::Update(float elapsed_ms) {
		switch (state) {

		case GameClient::State::Connecting: {
			if (Connect(Engine::IPEndPoint("::1", 27015))) {
				tick_count = 0.0f;
				total_elapsed_ms = 0.0f;
				state = Waiting;
			}
			break;
		}

		case GameClient::State::Waiting: {
			auto packet = std::make_shared<Engine::Packet>(Engine::PacketType::Ping);
			*packet << id << tick_count << total_elapsed_ms;
			connection.outgoing_packets.Append(packet);
			tick_count++;
			total_elapsed_ms += elapsed_ms;
			break;
		}

		default:
			break;

		}
	}

	void GameClient::Render(sf::RenderWindow& window) {
	}

	void GameClient::OnConnect() {
	}

	void GameClient::OnDisconnect() {
	}

	void GameClient::OnConnectFail() {
	}

	bool GameClient::ProcessPacket(std::shared_ptr<Engine::Packet> packet) {
		switch (packet->GetPacketType()) {
		case Engine::PacketType::Welcome: {
			*packet >> id;
			return true;
			break;
		}

		default:
			return false;
			break;
		}
	}

}