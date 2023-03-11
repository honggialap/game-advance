#pragma once
#ifndef __SERVER_BULLET_H__
#define __SERVER_BULLET_H__

#include "game_object.h"

namespace Server {

	// Forward declaration
	class GameServer;
	typedef GameServer* pGameServer;
	class World;
	typedef World* pWorld;

	class Bullet : public Engine::GameObject {
	protected:
		pGameServer game_server;
		pWorld world;

	protected:
		sf::Font font;
		sf::Text text;

	public:
		Bullet(Engine::pGame game, Engine::pScene scene);
		~Bullet();

	public:
		void Load(std::string data_path) override;
		void Unload() override;

		void Update(float elapsed) override;
		void Render(sf::RenderWindow& window) override;
	};
	typedef Bullet* pBullet;

}

#endif // !__SERVER_BULLET_H__
