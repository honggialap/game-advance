#pragma once
#ifndef __SERVER_TANK_H__
#define __SERVER_TANK_H__

#include "game_object.h"

// Forward declaration
class Game;
typedef Game* pGame;
class World;
typedef World* pWorld;

class Tank : public GameObject {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Tank(pGame game, pWorld world) : GameObject(game, world) {};

public:
	void Load(std::string data_path) override;
	void Unload() override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	void OnCollisionEnter(pGameObject other) override;
	void OnCollisionExit(pGameObject other) override;
};
typedef Tank* pTank;

#endif // !__SERVER_TANK_H__
