#pragma once
#ifndef __CLIENT_TANK_H__
#define __CLIENT_TANK_H__

#include "game_object.h"

// Forward declaration
class Game;
typedef Game* pGame;
class World;
typedef World* pWorld;

class Tank : public GameObject {
protected:
	bool player_control = false;
	int32_t movement_x = 0;
	int32_t movement_y = 0;

	sf::Texture texture;
	sf::Sprite sprite;

	b2BodyDef body_def;
	b2Body* body = nullptr;

	b2PolygonShape collider;

	b2FixtureDef fixture_def;
	b2Fixture* fixture = nullptr;

public:
	Tank(pGame game, pWorld world) : GameObject(game, world) {};

	void SetPlayerControl(bool player_control) { this->player_control = player_control; }
	void SetMovement(int32_t x, int32_t y) { movement_x = x; movement_y = y; }

	void Load(std::string data_path) override;
	void Unload() override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	void OnCollisionEnter(pGameObject other) override;
	void OnCollisionExit(pGameObject other) override;
};
typedef Tank* pTank;

#endif // !__CLIENT_TANK_H__
