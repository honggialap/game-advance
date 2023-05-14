#pragma once
#ifndef __CLIENT_TANK_H__
#define __CLIENT_TANK_H__

#include "game_object.h"

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
	float speed = 0.5f;


public:
	float last_known_x = 0;
	float last_known_y = 0;
	float latest_x = 0;
	float latest_y = 0;

	Tank(pGame game, pWorld world, uint32_t id, uint32_t type)
		: GameObject(game, world, id, type) {};
	~Tank() {};

	void SetPlayerId(uint32_t value) { player_id = value; }
	uint32_t GetPlayerId() { return player_id; }

	void SetPlayerControl(bool value) { player_control = value; }
	bool IsPlayerControl() { return player_control; }

	void SetMovement(int32_t x, int32_t y) { current_movement.x = x; current_movement.y = y; }

	void Load(std::string data_path) override;
	void Unload() override;

	void HandleInput(uint32_t tick) override;
	void ExecuteCommand(Command* command) override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	void OnCollisionEnter(GameObject* other) override;
	void OnCollisionExit(GameObject* other) override;

	void SendMoveCommand(uint32_t tick, MoveCommand move_command);
};
typedef Tank* pTank;

#endif // !__CLIENT_TANK_H__
