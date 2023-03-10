#pragma once
#ifndef __CLIENT_GAMECLIENT_H__
#define __CLIENT_GAMECLIENT_H__

#include "game.h"
#include "host_connection.h"

#define SCENE_TYPE_LOBBY 1
#define SCENE_TYPE_WORLD 2

namespace Client {

	class GameClient : public Engine::Game {
	protected:
		Engine::HostConnection host_connection;

	public:
		Engine::pScene CreateScene(unsigned int scene_type) override;

	protected:
		void Initialize(std::string data_path) override;
		void Shutdown() override;

		void Update(float elapsedMs) override;
		void Render(sf::RenderWindow& window) override;
	};
	typedef GameClient* pGameClient;

}

#endif // !__CLIENT_CLIENT_H__
