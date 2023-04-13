#pragma once
#ifndef __SERVER_GAMEOBJECT_H__
#define __SERVER_GAMEOBJECT_H__

#include "common.h"

// Forward declaration
class Game;
typedef Game* pGame;
class World;
typedef World* pWorld;

struct GameObjectState {
	uint32_t id;
	uint32_t type;

	float position_x;
	float position_y;

	float velocity_x;
	float velocity_y;

	GameObjectState(
		uint32_t id, 
		uint32_t type, 
		float position_x, 
		float position_y, 
		float velocity_x, 
		float velocity_y
	):
		id(id),
		type(type),
		position_x(position_x),
		position_y(position_y),
		velocity_x(velocity_x),
		velocity_y(velocity_y)
	{}
};
typedef GameObjectState* pGameObjectState;

class GameObject {
protected:
	pGame game;
	pWorld world;

	uint32_t id;
	uint32_t type;

	bool is_active;
	bool is_destroyed;

	float position_x;
	float position_y;

	float velocity_x;
	float velocity_y;

public:
	GameObject(
		pGame game,
		pWorld world,
		uint32_t id,
		uint32_t type,
		float position_x,
		float position_y,
		float velocity_x,
		float velocity_y
	) :
		game(game),
		world(world),
		id(id),
		type(type),
		position_x(position_x),
		position_y(position_y),
		velocity_x(velocity_x),
		velocity_y(velocity_y),
		is_active(false),
		is_destroyed(false)
	{};

	uint32_t GetId() { return id; }

	uint32_t GetType() { return type; }

	void SetActive(bool active) { is_active = active; }
	bool IsActive() { return is_active; }

	void Destroy() { is_destroyed = true; }
	bool IsDestroyed() { return is_destroyed; }

	void SetPosition(float x, float y) { position_x = x; position_y = y; }
	void GetPosition(float& x, float& y) { x = position_x; y = position_y; }

	void SetVelocity(float vx, float vy) { velocity_x = vx; velocity_y = vy; }
	void GetVelocity(float& vx, float& vy) { vx = velocity_x; vy = velocity_y; }

	virtual pGameObjectState Serialize() = 0;
	virtual bool Deserialize(pGameObjectState game_object_state) = 0;

	virtual void Load(std::string data_path) = 0;
	virtual void Unload() = 0;

	virtual void Update(float elapsed) = 0;
	virtual void Render(sf::RenderWindow& window) = 0;

	virtual void OnCollisionEnter(GameObject* other) = 0;
	virtual void OnCollisionExit(GameObject* other) = 0;
};
typedef GameObject* pGameObject;

#endif // !__SERVER_GAMEOBJECT_H__
