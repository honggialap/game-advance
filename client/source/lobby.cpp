#include "lobby.h"
#include "game_client.h"

namespace Client {

	Lobby::Lobby(Engine::pGame game) : Engine::Scene(game) {
		game_client = static_cast<pGameClient>(game);
	}

	Lobby::~Lobby() {
	}

	void Lobby::Load(std::string data_path) {
		std::ifstream data_file(data_path);
		nlohmann::json data = nlohmann::json::parse(data_file);
		//
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

}