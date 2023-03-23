#pragma once
#ifndef __CLIENT_LOBBY_H__
#define __CLIENT_LOBBY_H__

#include "scene.h"
#include "game_object.h"

namespace Client {

	// Forward declaration
	class GameClient;
	typedef GameClient* pGameClient;

	class Lobby : public Engine::Scene {
	protected:
		pGameClient game_client;

	public:
		Lobby(Engine::pGame game);
		~Lobby();

	public:
		void Load(std::string data_path) override;
		void Unload() override;

		void Update(float elapsed) override;
		void Render(sf::RenderWindow& window) override;

		Engine::pGameObject CreateGameObject(unsigned int game_object_type);
	};
	typedef Lobby* pLobby;

}

#endif // !__CLIENT_LOBBY_H__
