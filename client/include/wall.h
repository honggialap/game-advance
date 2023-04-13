#pragma once
#ifndef __CLIENT_WALL_H__
#define __CLIENT_WALL_H__

#include "game_object.h"

struct WallState : public GameObjectState {
	WallState(
		uint32_t id,
		uint32_t type,
		float position_x,
		float position_y,
		float velocity_x,
		float velocity_y
	) : GameObjectState(id, type, position_x, position_y, velocity_x, velocity_y) {
	}
};
typedef WallState* pWallState;

class Wall : public GameObject {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	b2BodyDef body_def;
	b2Body* body = nullptr;

	b2PolygonShape collider;

	b2FixtureDef fixture_def;
	b2Fixture* fixture = nullptr;

public:
	Wall(
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
typedef Wall* pWall;

#endif // !__CLIENT_WALL_H__
