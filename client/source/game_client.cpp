#include "game_client.h"
#include "lobby.h"
#include "world.h"

namespace Client {

	Engine::pScene GameClient::CreateScene(unsigned int scene_type) {
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

	void GameClient::Initialize(std::string data_path) {
		Engine::Game::Initialize(data_path);
		//
	}

	void GameClient::Shutdown() {
		//
		Engine::Game::Shutdown();
	}

	void GameClient::Update(float elapsedMs) {
		//
		Engine::Game::Update(elapsedMs);
		//
	}

	void GameClient::Render(sf::RenderWindow& window) {
		//
		Engine::Game::Render(window);
		//
	}

}