#pragma once
#ifndef __CLIENT_BULLET_H__
#define __CLIENT_BULLET_H__

#include "game_object.h"

struct BulletGameState : public GameState {
	BulletGameState(
		uint32_t id,
		uint32_t type,
		float position_x,
		float position_y,
		float velocity_x,
		float velocity_y
	) :
		GameState(
			id,
			type,
			position_x,
			position_y,
			velocity_x,
			velocity_y
		)
	{}
};
typedef std::unique_ptr<BulletGameState> pBulletGameState;

class Bullet : public GameObject {
public:
	Bullet(pGame game, pWorld world, uint32_t id, uint32_t type)
		: GameObject(game, world, id, type) {};

	void Load(std::string data_path) override;
	void Unload() override;

	GameState* Serialize() override;
	void Deserialize(GameState* game_state) override;

	void HandleInput() override;
	void ExecuteCommand(Command* command) override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	void OnCollisionEnter(pGameObject other) override;
	void OnCollisionExit(pGameObject other) override;
};
typedef Bullet* pBullet;

#endif // !__CLIENT_BULLET_H__
