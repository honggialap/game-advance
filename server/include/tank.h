#pragma once
#ifndef __SERVER_TANK_H__
#define __SERVER_TANK_H__

#include "game_object.h"

struct TankRecord : public Record {
	uint32_t player_id;

	int32_t current_movement_x;
	int32_t current_movement_y;

	TankRecord(
		uint32_t game_object_id,
		uint32_t game_object_type,
		float position_x,
		float position_y,
		float velocity_x,
		float velocity_y,
		uint32_t player_id,
		int32_t current_movement_x,
		int32_t current_movement_y
	) :
		Record(
			game_object_id,
			game_object_type,
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
typedef std::unique_ptr<TankRecord> pTankRecord;

#define TANK_COMMAND_TYPE_MOVE 1
struct MoveCommand : public Command {
	int32_t x;
	int32_t y;

	MoveCommand(
		uint32_t game_object_id,
		int32_t x,
		int32_t y
	) :
		Command(game_object_id),
		x(x),
		y(y)
	{
		command_type = TANK_COMMAND_TYPE_MOVE;
	}
};
typedef std::unique_ptr<MoveCommand> pMoveCommand;

#define TANK_COMMAND_TYPE_SHOOT 2
struct ShootCommand : public Command {
	ShootCommand(
		uint32_t game_object_id
	) :
		Command(game_object_id)
	{
		command_type = TANK_COMMAND_TYPE_SHOOT;
	}
};
typedef std::unique_ptr<ShootCommand> pShootCommand;

class Tank : public GameObject {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	uint32_t player_id = 0;
	bool player_control = false;

	sf::Vector2i current_movement;
	float speed = 1;

public:
	Tank(pGame game, pWorld world, uint32_t id, uint32_t type)
		: GameObject(game, world, id, type) {};

	void SetPlayerId(uint32_t value) { player_id = value; }
	uint32_t GetPlayerId() { return player_id; }

	void SetPlayerControl(bool value) { player_control = value; }
	bool IsPlayerControl() { return player_control; }

	void SetMovement(int32_t x, int32_t y) { current_movement.x = x; current_movement.y = y; }

	void Load(std::string data_path) override;
	void Unload() override;

	Record* Serialize() override;
	void Deserialize(Record* record) override;

	void HandleInput(uint32_t tick) override;
	void ExecuteCommand(Command* command) override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	void OnCollisionEnter(GameObject* other) override;
	void OnCollisionExit(GameObject* other) override;
};
typedef Tank* pTank;

#endif // !__SERVER_TANK_H__
