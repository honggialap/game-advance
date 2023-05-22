#pragma once
#ifndef __CLIENT_GAMEOBJECT_H__
#define __CLIENT_GAMEOBJECT_H__

#include "common.h"

// Forward declaration
class Game;
typedef Game* pGame;
class World;
typedef World* pWorld;

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
	Game* game = nullptr;
	World* world = nullptr;

	std::string name;
	uint32_t id = 0;
	uint32_t type = 0;
	uint32_t layer = 0;

	bool is_active = false;
	bool is_destroyed = false;

	b2BodyDef body_def;
	b2Body* body = nullptr;
	b2PolygonShape collider;
	b2FixtureDef fixture_def;
	b2Fixture* fixture = nullptr;

public:
	GameObject(Game* game, World* world);
	virtual ~GameObject() = 0;

	void SetName(std::string value);
	std::string GetName();

	void SetId(uint32_t value);
	uint32_t GetId();
	
	void SetType(uint32_t value);
	uint32_t GetType();

	void SetLayer(uint32_t value);
	uint32_t GetLayer();

	void SetActive(bool active);
	bool IsActive();

	void Destroy();
	bool IsDestroyed();

	void SetPosition(float x, float y);
	void GetPosition(float& x, float& y);

	void SetVelocity(float vx, float vy);
	void GetVelocity(float& vx, float& vy);

	virtual void Load(std::string data_path) = 0;
	virtual void Unload() = 0;

	virtual void HandleInput(uint32_t tick) = 0;
	virtual void ExecuteCommand(Command* command) = 0;

	virtual void Update(float elapsed) = 0;
	virtual void Render(sf::RenderWindow& window) = 0;

	virtual void OnCollisionEnter(GameObject* other) = 0;
	virtual void OnCollisionExit(GameObject* other) = 0;
};
typedef std::unique_ptr<GameObject> pGameObject;

#endif // !__CLIENT_GAMEOBJECT_H__
