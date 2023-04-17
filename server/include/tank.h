#pragma once
#ifndef __SERVER_TANK_H__
#define __SERVER_TANK_H__

#include "game_object.h"

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

	void Load(std::string data_path) override;
	void Unload() override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	void OnCollisionEnter(pGameObject other) override;
	void OnCollisionExit(pGameObject other) override;
};
typedef Tank* pTank;

#endif // !__SERVER_TANK_H__
