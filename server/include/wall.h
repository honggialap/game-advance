#pragma once
#ifndef __SERVER_WALL_H__
#define __SERVER_WALL_H__

#include "game_object.h"

struct WallState : public GameObjectState {
	WallState(
		uint32_t id,
		uint32_t type,
		float position_x,
		float position_y,
		float velocity_x,
		float velocity_y
	): 
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
typedef WallState* pWallState;

class Wall : public GameObject {
public:
	Wall(pGame game, pWorld world, uint32_t id, uint32_t type) 
		: GameObject(game, world, id, type) {};

	void Load(std::string data_path) override;
	void Unload() override;

	pGameObjectState Serialize() override;
	void Deserialize(pGameObjectState game_object_state) override;

	void ExecuteCommand(pCommand command) override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	void OnCollisionEnter(pGameObject other) override;
	void OnCollisionExit(pGameObject other) override;
};
typedef Wall* pWall;

#endif // !__SERVER_WALL_H__
