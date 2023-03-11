#pragma once
#ifndef __SERVER_WORLD_H__
#define __SERVER_WORLD_H__

#include "scene.h"
#include "game_object.h"

#define ACTOR_TYPE_TANK		1
#define ACTOR_TYPE_BULLET	2
#define ACTOR_TYPE_WALL		3

namespace Server {

	// Forward declaration
	class GameServer;
	typedef GameServer* pGameServer;

	class World : public Engine::Scene {
	protected:
		pGameServer game_server;

	protected:
		sf::View camera;

		std::unique_ptr<Engine::GameObject> tank;
		std::unique_ptr<Engine::GameObject> bullet;
		std::unique_ptr<Engine::GameObject> wall;

	public:
		World(Engine::pGame game);
		~World();

	public:
		Engine::pGameObject CreateGameObject(unsigned int game_object_type);

		void Load(std::string data_path) override;
		void Unload() override;

		void Update(float elapsed) override;
		void Render(sf::RenderWindow& window) override;

	public:
		sf::View& GetCamera();
	};

}

#endif // !__SERVER_WORLD_H__
