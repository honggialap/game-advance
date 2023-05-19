#pragma once
#ifndef __SERVER_GAMEOBJECT_H__
#define __SERVER_GAMEOBJECT_H__

#include "common.h"

// Forward declaration
class Game;
typedef Game* pGame;
class World;
typedef World* pWorld;

struct Record {
	uint32_t game_object_id;
	uint32_t game_object_type;

	Record(uint32_t id, uint32_t type) :
		game_object_id(id),
		game_object_type(type)
	{}
};
typedef std::unique_ptr<Record> pRecord;

struct Command {
	uint32_t game_object_id;
	uint32_t command_type;

	Command(uint32_t game_object_id) :
		game_object_id(game_object_id),
		command_type(0)
	{}
};
typedef std::unique_ptr<Command> pCommand;

class GameObject {
protected:
	pGame game;
	pWorld world;

	std::string name;
	uint32_t id;
	uint32_t type;
	uint32_t layer;

	std::string resource_path;

	bool is_active;
	bool is_destroyed;

	b2BodyDef body_def;
	b2Body* body = nullptr;
	b2PolygonShape collider;
	b2FixtureDef fixture_def;
	b2Fixture* fixture = nullptr;

public:
	void SetGame(pGame value) { game = value; }
	pGame GetGame() { return game; }

	void SetWorld(pWorld value) { world = value; }
	pWorld GetWorld() { return world; }

	void SetName(std::string value) { name = value; }
	std::string GetName() { return name; }

	void SetId(uint32_t value) { id = value; }
	uint32_t GetId() { return id; }

	void SetType(uint32_t value) { type = value; }
	uint32_t GetType() { return type; }

	void SetLayer(uint32_t value) { layer = value; }
	uint32_t GetLayer() { return layer; }

	void SetResourcePath(std::string value) { resource_path = value; }
	std::string GetResourcePath() { return resource_path; }

	void SetActive(bool active) { is_active = active; }
	bool IsActive() { return is_active; }

	void Destroy() { is_destroyed = true; }
	bool IsDestroyed() { return is_destroyed; }

	void SetPosition(float x, float y) { body->SetTransform(b2Vec2(x / PIXEL_PER_METER, y / PIXEL_PER_METER), 0); }
	void GetPosition(float& x, float& y) { x = body->GetPosition().x * PIXEL_PER_METER; y = body->GetPosition().y * PIXEL_PER_METER; }

	void SetVelocity(float vx, float vy) { body->SetLinearVelocity(b2Vec2(vx / PIXEL_PER_METER, vy / PIXEL_PER_METER)); }
	void GetVelocity(float& vx, float& vy) { vx = body->GetPosition().x * PIXEL_PER_METER; vy = body->GetPosition().y * PIXEL_PER_METER; }

	virtual void Load(std::string data_path) = 0;
	virtual void Unload() = 0;

	virtual void Serialize(uint32_t tick) = 0;
	virtual void Deserialize(Record* record) = 0;

	virtual void HandleInput(uint32_t tick) = 0;
	virtual void ExecuteCommand(Command* command) = 0;

	virtual void Update(float elapsed) = 0;
	virtual void Render(sf::RenderWindow& window) = 0;

	virtual void OnCollisionEnter(GameObject* other) = 0;
	virtual void OnCollisionExit(GameObject* other) = 0;
};
typedef std::unique_ptr<GameObject> pGameObject;

#endif // !__SERVER_GAMEOBJECT_H__
