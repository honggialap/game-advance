#pragma once
#ifndef __SERVER_BULLET_H__
#define __SERVER_BULLET_H__

#include "game_object.h"

class Bullet : public GameObject {
public:
	Bullet(pGame game, pWorld world, uint32_t id, uint32_t type)
		: GameObject(game, world, id, type) {};

	void Load(std::string data_path) override;
	void Unload() override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	void OnCollisionEnter(pGameObject other) override;
	void OnCollisionExit(pGameObject other) override;
};
typedef Bullet* pBullet;

#endif // !__SERVER_BULLET_H__
