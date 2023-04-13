#pragma once
#ifndef __SERVER_BULLET_H__
#define __SERVER_BULLET_H__

#include "game_object.h"

// Forward declaration
class Game;
typedef Game* pGame;
class World;
typedef World* pWorld;

struct BulletState : public GameObjectState {
	BulletState(
		uint32_t id,
		uint32_t type,
		float position_x,
		float position_y,
		float velocity_x,
		float velocity_y
	) :
		GameObjectState(
			id,
			type,
			position_x,
			position_y,
			velocity_x,
			velocity_y
		)
	{}
};
typedef BulletState* pBulletState;

class Bullet : public GameObject {
protected:
	sf::Font font;
	sf::Text text;

public:
	Bullet(
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
typedef Bullet* pBullet;

#endif // !__SERVER_BULLET_H__
