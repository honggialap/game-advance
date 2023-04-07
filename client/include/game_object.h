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

	uint32_t game_object_id;
	uint32_t networks_id;
	bool sync;

public:
	GameObject(pGame game, pWorld world) : game(game), world(world) {};

	void SetId(uint32_t id) { game_object_id = id; }
	void SetNetworksId(uint32_t id) { networks_id = id; }
	void SetSync(bool sync) { this->sync = sync; }

	virtual void Load(std::string data_path) = 0;
	virtual void Unload() = 0;

	virtual void Update(float elapsed) = 0;
	virtual void Render(sf::RenderWindow& window) = 0;

	virtual void OnCollisionEnter(GameObject* other) = 0;
	virtual void OnCollisionExit(GameObject* other) = 0;
};
typedef GameObject* pGameObject;

#endif // !__CLIENT_GAMEOBJECT_H__
