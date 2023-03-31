#pragma once
#ifndef __CLIENT_BULLET_H__
#define __CLIENT_BULLET_H__

#include "game_object.h"

// Forward declaration
class Game;
typedef Game* pGame;
class World;
typedef World* pWorld;

class Bullet : public GameObject {
protected:
	sf::Font font;
	sf::Text text;

public:
	Bullet(pGame game, pWorld world) : GameObject(game, world) {};

	void Load(std::string data_path) override;
	void Unload() override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	void OnCollisionEnter(GameObject* other) override;
	void OnCollisionExit(GameObject* other) override;
};
typedef Bullet* pBullet;

#endif // !__CLIENT_BULLET_H__
