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
		sf::Texture texture;
		sf::Sprite sprite;

		b2BodyDef body_def;
		b2Body* body = nullptr;

		b2PolygonShape collider;

		b2FixtureDef fixture_def;
		b2Fixture* fixture = nullptr;

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

#endif // !__CLIENT_TANK_H__
