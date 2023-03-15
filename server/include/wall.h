#pragma once
#ifndef __SERVER_WALL_H__
#define __SERVER_WALL_H__

#include "game_object.h"

namespace Server {

	// Forward declaration
	class GameServer;
	typedef GameServer* pGameServer;
	class World;
	typedef World* pWorld;

	class Wall : public Engine::GameObject {
	protected:
		pGameServer game_server;
		pWorld world;

	public:
		Wall(Engine::pGame game, Engine::pScene scene);
		~Wall();

	protected:
		sf::SoundBuffer sfx_buffer;
		sf::Sound sfx;
		sf::Music music;

	public:
		void Load(std::string data_path) override;
		void Unload() override;

		void Update(float elapsed) override;
		void Render(sf::RenderWindow& window) override;

		void OnCollisionEnter(Engine::pGameObject other) override;
		void OnCollisionExit(Engine::pGameObject other) override;
	};
	typedef Wall* pWall;

}

#endif // !__SERVER_WALL_H__
