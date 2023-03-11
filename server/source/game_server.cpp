#include "game_server.h"
#include "lobby.h"
#include "world.h"

namespace Server {

	Engine::pScene GameServer::CreateScene(unsigned int scene_type) {
		switch (scene_type) {
		case SCENE_TYPE_LOBBY:
			return new Lobby(this);
			break;

		case SCENE_TYPE_WORLD:
			return new World(this);
			break;

		default:
			return nullptr;
			break;
		}
	}

	void GameServer::Initialize(std::string data_path) {
		Engine::Game::Initialize(data_path);
		listening_thread = std::thread(
			[this]() {
				if (remote_connection.Listen("27015")) {
					while (remote_connection.Accept()) {
					}
					remote_connection.Shutdown();
				}
			}
		);
	}

	void GameServer::Shutdown() {
		if (listening_thread.joinable())
			listening_thread.join();
		Engine::Game::Shutdown();
	}

	void GameServer::Update(float elapsedMs) {
		//
		Engine::Game::Update(elapsedMs);
		//
	}

	void GameServer::Render(sf::RenderWindow& window) {
		//
		Engine::Game::Render(window);
		//
	}

}
