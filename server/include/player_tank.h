#pragma once
#ifndef __SERVER_PLAYER_TANK_H__
#define __SERVER_PLAYER_TANK_H__

#include "game_object.h"

struct PlayerTankRecord : public Record {
	float position_x, position_y;
	float velocity_x, velocity_y;
	int32_t movement_x, movement_y;

	PlayerTankRecord(
		uint32_t id, uint32_t type,
		float position_x, float position_y,
		float velocity_x, float velocity_y,
		int32_t movement_x, int32_t movement_y
	) :
		Record(id, type),
		position_x(position_x), position_y(position_y),
		velocity_x(velocity_x), velocity_y(velocity_y),
		movement_x(movement_x), movement_y(movement_y)
	{}
};
typedef std::unique_ptr<PlayerTankRecord> pPlayerTankRecord;

#define PLAYER_TANK_COMMAND_MOVE 1
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
		command_type = PLAYER_TANK_COMMAND_MOVE;
	}
};
typedef std::unique_ptr<MoveCommand> pMoveCommand;

#define PLAYER_TANK_COMMAND_SHOOT 2
struct ShootCommand : public Command {
	ShootCommand(
		uint32_t game_object_id
	) :
		Command(game_object_id)
	{
		command_type = PLAYER_TANK_COMMAND_SHOOT;
	}
};
typedef std::unique_ptr<ShootCommand> pShootCommand;

class PlayerTank : public GameObject {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	uint32_t player_id = 0;
	uint32_t team = 0;

	sf::Vector2i current_movement;
	float speed = 0.5f;

public:
	static PlayerTank* Create(pGame game, pWorld world, nlohmann::json& data);

	void SetPlayerId(uint32_t value) { player_id = value; }
	uint32_t GetPlayerId() { return player_id; }

	void SetTeam(uint32_t value) { team = value; }
	uint32_t GetTeam() { return team; }

	void SetMovement(int32_t x, int32_t y) { current_movement.x = x; current_movement.y = y; }
	void GetMovement(int32_t& x, int32_t& y) { x = current_movement.x; y = current_movement.y; }

	void Load(std::string data_path) override;
	void Unload() override;

	void Serialize(uint32_t tick) override;
	void Deserialize(Record* record) override;

	void HandleInput(uint32_t tick) override;
	void ExecuteCommand(Command* command) override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	void OnCollisionEnter(GameObject* other) override;
	void OnCollisionExit(GameObject* other) override;
};
typedef PlayerTank* pPlayerTank;

#endif // !__SERVER_PLAYER_TANK_H__
