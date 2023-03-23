#include "lobby.h"
#include "game_server.h"

namespace Server {

	Lobby::Lobby(Engine::pGame game) : Engine::Scene(game) {
		game_server = static_cast<pGameServer>(game);
	}

	Lobby::~Lobby() {
	}

	void Lobby::Load(std::string data_path) {
		std::ifstream data_file(data_path);
		nlohmann::json data = nlohmann::json::parse(data_file);
	}

	void Lobby::Unload() {
		//
	}

	void Lobby::Update(float elapsed) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {
			game->PlayScene(1);
		}
	}

	void Lobby::Render(sf::RenderWindow& window) {
		//
	}

	Engine::pGameObject Lobby::CreateGameObject(unsigned int game_object_type) {
		switch (game_object_type) {
		default:
			return nullptr;
			break;
		}
	}
}