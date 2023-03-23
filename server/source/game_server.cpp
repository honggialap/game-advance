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

	void GameServer::OnConnect(Engine::Connection& connection) {
	}

	void GameServer::OnDisconnect(Engine::Connection& connection) {
	}

	bool GameServer::ProcessPacket(std::shared_ptr<Engine::Packet> packet) {
		return false;
	}

	void GameServer::Initialize(std::string data_path) {
		Engine::Game::Initialize(data_path);

		std::ifstream data_file(data_path);
		nlohmann::json data = nlohmann::json::parse(data_file);


	}

	void GameServer::Shutdown() {
		Engine::Game::Shutdown();
	}

}
