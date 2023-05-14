#pragma once
#ifndef __SERVER_WORLD_H__
#define __SERVER_WORLD_H__

#include "scene.h"
#include "game_object.h"
#include "game.h"

#define ACTOR_TYPE_TANK		1
#define ACTOR_TYPE_BULLET	2
#define ACTOR_TYPE_WALL		3

class World : public b2ContactListener {
public:
	b2Vec2 gravity;
	b2World* physics_world = nullptr;

	uint32_t game_object_id = 1000;
	std::map<uint32_t, pGameObject> game_objects;
	std::map<uint32_t, std::vector<pCommand>> commands;
	std::map<uint32_t, std::vector<pRecord>> records;

	uint32_t latest_tick = 0;
	uint32_t rollback_tick = 0;
	bool rollback = false;
	uint32_t tick_per_game_state = 8;

	World();
	~World();

	GameObject* CreateGameObject(Game* game, uint32_t game_object_type, float position_x, float position_y);

	void HandleInput(uint32_t tick);
	void Step(uint32_t tick, float elapsed);

	void TrimCommands(uint32_t threshold);
	
	void TrimRecords(uint32_t threshold);
	void TrimRecords(uint32_t from, uint32_t to);

	void Serialize(uint32_t tick);
	void Deserialize(uint32_t tick);

	b2World* GetPhysics();
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
};
typedef World* pWorld;

#endif // !__SERVER_WORLD_H__
