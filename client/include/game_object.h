#pragma once
#ifndef __CLIENT_GAMEOBJECT_H__
#define __CLIENT_GAMEOBJECT_H__

#include "common.h"

// Forward declaration
class Game;
typedef Game* pGame;
class World;
typedef World* pWorld;

class GameObject : public sf::Transformable {
protected:
	pGame game;
	pWorld world;

public:
	GameObject(pGame game, pWorld world) : game(game), world(world) {};

	virtual void Load(std::string data_path) = 0;
	virtual void Unload() = 0;

	virtual void Update(float elapsed) = 0;
	virtual void Render(sf::RenderWindow& window) = 0;

	virtual void OnCollisionEnter(GameObject* other) = 0;
	virtual void OnCollisionExit(GameObject* other) = 0;
};
typedef GameObject* pGameObject;

#endif // !__CLIENT_GAMEOBJECT_H__
