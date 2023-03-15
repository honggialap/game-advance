#pragma once
#ifndef __SERVER_TANK_H__
#define __SERVER_TANK_H__

#include "game_object.h"

namespace Server {
	
	// Forward declaration
	class GameServer;
	typedef GameServer* pGameServer;
	class World;
	typedef World* pWorld;

	class Tank : public Engine::GameObject {
	protected:
		pGameServer game_server;
		pWorld world;

	protected:
		sf::Texture texture;
		sf::Sprite sprite;

	public:
		Tank(Engine::pGame game, Engine::pScene scene);
		~Tank();

	public:
		void Load(std::string data_path) override;
		void Unload() override;

		void Update(float elapsed) override;
		void Render(sf::RenderWindow& window) override;

		void OnCollisionEnter(Engine::pGameObject other) override;
		void OnCollisionExit(Engine::pGameObject other) override;
	};
	typedef Tank* pTank;

}

#endif // !__SERVER_TANK_H__
