#pragma once
#ifndef __CLIENT_BULLET_H__
#define __CLIENT_BULLET_H__

#include "game_object.h"

namespace Client {

	// Forward declaration
	class GameClient;
	typedef GameClient* pGameClient;
	class World;
	typedef World* pWorld;

	class Bullet : public Engine::GameObject {
	protected:
		pGameClient game_client;
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

#endif // !__CLIENT_BULLET_H__
