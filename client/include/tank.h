#pragma once
#ifndef __CLIENT_TANK_H__
#define __CLIENT_TANK_H__

#include "game_object.h"
#include "animation.h"

namespace Client {
	
	// Forward declaration
	class GameClient;
	typedef GameClient* pGameClient;
	class World;
	typedef World* pWorld;

	class Tank : public Engine::GameObject {
	protected:
		pGameClient game_client;
		pWorld world;

	protected:
		Engine::Animation animation;

	public:
		Tank(Engine::pGame game, Engine::pScene scene);
		~Tank();

	public:
		void Load(std::string data_path) override;
		void Unload() override;
		
		void Update(float elapsed) override;
		void Render(sf::RenderWindow& window) override;
	};
	typedef Tank* pTank;

}

#endif // !__CLIENT_TANK_H__
