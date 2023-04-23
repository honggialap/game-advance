#pragma once
#ifndef __SERVER_TANK_H__
#define __SERVER_TANK_H__

#include "game_object.h"

struct TankState : public GameObjectState {
	uint32_t player_id;

	int32_t current_movement_x;
	int32_t current_movement_y;

	TankState(
		uint32_t id,
		uint32_t type,
		float position_x,
		float position_y,
		float velocity_x,
		float velocity_y,
		uint32_t player_id,
		int32_t current_movement_x,
		int32_t current_movement_y
	) :
		GameObjectState(
			id,
			type,
			position_x,
			position_y,
			velocity_x,
			velocity_y
		),
		player_id(player_id),
		current_movement_x(current_movement_x),
		current_movement_y(current_movement_y)
	{}
};
typedef TankState* pTankState;

class Tank : public GameObject {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	uint32_t player_id = 0;
	sf::Vector2i current_movement;

public:
	Tank(pGame game, pWorld world, uint32_t id, uint32_t type) 
		: GameObject(game, world, id, type) {};

	void SetPlayerId(uint32_t value) { player_id = value; }
	uint32_t GetPlayerId() { return player_id; }

	void SetMovement(int32_t x, int32_t y) { current_movement.x = x; current_movement.y = y; }

	pGameObjectState Serialize() override;
	void Deserialize(pGameObjectState game_object_state) override;

	void ExecuteCommand(uint32_t tick) override;

	void Load(std::string data_path) override;
	void Unload() override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	void OnCollisionEnter(pGameObject other) override;
	void OnCollisionExit(pGameObject other) override;
};
typedef Tank* pTank;

#endif // !__SERVER_TANK_H__
