#pragma once
#ifndef __CLIENT_TANK_H__
#define __CLIENT_TANK_H__

#include "game_object.h"
#include "command.h"

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

	void HandleInput();
	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	void OnCollisionEnter(pGameObject other) override;
	void OnCollisionExit(pGameObject other) override;

	void SendMoveCommand(pMoveCommand move_command);
};
typedef Tank* pTank;

#endif // !__CLIENT_TANK_H__
