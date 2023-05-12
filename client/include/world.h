#pragma once
#ifndef __CLIENT_WORLD_H__
#define __CLIENT_WORLD_H__

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
	uint32_t ack_tick = 0;
	bool just_got_game_state = false;
	uint32_t tick_per_game_state = 8;

	World();
	~World();

	GameObject* CreateGameObject(Game* game, uint32_t game_object_type, float position_x, float position_y);

	void Serialize(uint32_t tick);
	void Deserialize(uint32_t tick);

	b2World* GetPhysics();
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
};
typedef World* pWorld;

#endif // !__CLIENT_WORLD_H__
