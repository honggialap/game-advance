#include "game_server.h"

#include <iostream>
#include <string>

namespace Server {

	void GameServer::Initialize() {
		Engine::Game::Initialize();
		printf("GameServer::Initialize()\n");
	}

	void GameServer::Shutdown() {
		Engine::Game::Shutdown();
		printf("GameServer::Shutdown()\n");
	}

	void GameServer::Update() {
		Engine::Game::Update();
		printf("GameServer::Update()\n");
	}

	void GameServer::Render() {
		Engine::Game::Update();
		printf("GameServer::Render()\n");
	}

	void GameServer::CreateScene() {
		printf("GameServer::CreateScene()\n");
	}

}