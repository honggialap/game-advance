#pragma once
#ifndef __SERVER_GAMECSERVER_H__
#define __SERVER_GAMECSERVER_H__

#include "game.h"

#define SCENE_TYPE_LOBBY	1
#define SCENE_TYPE_WORLD	2

namespace Server {

	class GameServer : public Engine::Game {
	public:
		Engine::pScene CreateScene(unsigned int scene_type) override;

	protected:
		void Initialize(std::string data_path) override;
		void Shutdown() override;

		void Update(float elapsedMs) override;
		void Render(sf::RenderWindow& window) override;
	};
	typedef GameServer* pGameServer;

}

#endif // !__SERVER_GAMECSERVER_H__
