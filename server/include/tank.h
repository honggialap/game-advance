#pragma once
#ifndef __SERVER_TANK_H__
#define __SERVER_TANK_H__

#include "game_object.h"

// Forward declaration
class Game;
typedef Game* pGame;
class World;
typedef World* pWorld;

struct TankState : public GameObjectState {
	uint32_t player_id;

	TankState(
		uint32_t id,
		uint32_t type,
		float position_x,
		float position_y,
		float velocity_x,
		float velocity_y,
		uint32_t player_id
	) :
		GameObjectState(
			id, 
			type, 
			position_x, 
			position_y, 
			velocity_x, 
			velocity_y
		),
		player_id(player_id)
	{}
};
typedef TankState* pTankState;

class Tank : public GameObject {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	b2BodyDef body_def;
	b2Body* body = nullptr;

	b2PolygonShape collider;

	b2FixtureDef fixture_def;
	b2Fixture* fixture = nullptr;

public:
	uint32_t player_id = 0;

	Tank(
		pGame game,
		pWorld world,
		uint32_t id,
		uint32_t type,
		float position_x,
		float position_y,
		float velocity_x,
		float velocity_y
	) : GameObject(game, world, id, type, position_x, position_y, velocity_x, velocity_y) {
	};

	pGameObjectState Serialize() override;
	bool Deserialize(pGameObjectState game_object_state) override;

	void Load(std::string data_path) override;
	void Unload() override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	void OnCollisionEnter(pGameObject other) override;
	void OnCollisionExit(pGameObject other) override;
};
typedef Tank* pTank;

#endif // !__SERVER_TANK_H__
