#pragma once
#ifndef __CLIENT_WORLD_H__
#define __CLIENT_WORLD_H__

#include "scene.h"
#include "game_object.h"

#define ACTOR_TYPE_TANK		1
#define ACTOR_TYPE_BULLET	2
#define ACTOR_TYPE_WALL		3

namespace Client {

	// Forward declaration
	class GameClient;
	typedef GameClient* pGameClient;

	class World : public Engine::Scene {
	protected:
		pGameClient game_client;

	protected:
		sf::View camera;
		
		b2Vec2 gravity;
		b2World* physics;

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
		b2World* GetPhysics();
	};
	typedef World* pWorld;

}

#endif // !__CLIENT_WORLD_H__
