#pragma once
#ifndef __SERVER_LOBBY_H__
#define __SERVER_LOBBY_H__

#include "scene.h"

namespace Server {

	// Forward declaration
	class GameServer;
	typedef GameServer* pGameServer;
	
	class Lobby : public Engine::Scene {
	protected:
		pGameServer game_server;

	public:
		Lobby(Engine::pGame game);
		~Lobby();

	public:
		void Load(std::string data_path) override;
		void Unload() override;

		void Update(float elapsed) override;
		void Render(sf::RenderWindow& window) override;
	};
	typedef Lobby* pLobby;

}




#endif // !__SERVER_LOBBY_H__
