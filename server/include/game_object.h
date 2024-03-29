#pragma once
#ifndef __SERVER_GAMEOBJECT_H__
#define __SERVER_GAMEOBJECT_H__

#include "common.h"
#include "command.h"

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
	) :
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

	b2BodyDef body_def;
	b2Body* body = nullptr;
	b2PolygonShape collider;
	b2FixtureDef fixture_def;
	b2Fixture* fixture = nullptr;

public:
	std::deque<pCommand> commands;

	GameObject(
		pGame game,
		pWorld world,
		uint32_t id,
		uint32_t type
	) :
		game(game),
		world(world),
		id(id),
		type(type),
		is_active(false),
		is_destroyed(false)
	{};

	uint32_t GetId() { return id; }
	uint32_t GetType() { return type; }

	void SetActive(bool active) { is_active = active; }
	bool IsActive() { return is_active; }

	void Destroy() { is_destroyed = true; }
	bool IsDestroyed() { return is_destroyed; }

	void SetPosition(float x, float y) { body->SetTransform(b2Vec2(x / PIXEL_PER_METER, y / PIXEL_PER_METER), 0); }
	void GetPosition(float& x, float& y) { x = body->GetPosition().x * PIXEL_PER_METER; y = body->GetPosition().y * PIXEL_PER_METER; }

	void SetVelocity(float vx, float vy) { body->SetLinearVelocity(b2Vec2(vx / PIXEL_PER_METER, vy / PIXEL_PER_METER)); }
	void GetVelocity(float& vx, float& vy) { vx = body->GetPosition().x * PIXEL_PER_METER; vy = body->GetPosition().y * PIXEL_PER_METER; }

	virtual pGameObjectState Serialize() = 0;
	virtual void Deserialize(pGameObjectState game_object_state) = 0;

	virtual void ExecuteCommand(uint32_t tick) = 0;

	virtual void Load(std::string data_path) = 0;
	virtual void Unload() = 0;

	virtual void Update(float elapsed) = 0;
	virtual void Render(sf::RenderWindow& window) = 0;

	virtual void OnCollisionEnter(GameObject* other) = 0;
	virtual void OnCollisionExit(GameObject* other) = 0;
};
typedef GameObject* pGameObject;

#endif // !__SERVER_GAMEOBJECT_H__
