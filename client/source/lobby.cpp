#include "lobby.h"
#include "game_client.h"

namespace Client {

	Lobby::Lobby(Engine::pGame game) : Engine::Scene(game) {
		game_client = static_cast<pGameClient>(game);
	}

	Lobby::~Lobby() {
	}

	void Lobby::Load(std::string data_path) {
	}

	void Lobby::Unload() {
	}

	void Lobby::Update(float elapsed) {
	}

	void Lobby::Render(sf::RenderWindow& window) {
	}

	Engine::pGameObject Lobby::CreateGameObject(unsigned int game_object_type){
		switch (game_object_type) {
		default:
			return nullptr;
			break;
		}
	}

}