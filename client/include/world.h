#pragma once
#ifndef __CLIENT_WORLD_H__
#define __CLIENT_WORLD_H__

#include "game_object.h"
#include "game.h"

#pragma region ACTOR_TYPE_DEFINITION
#define ACTOR_GAME_MASTER				uint32_t(	0001	)
															
#define ACTOR_PLAYER_TANK				uint32_t(	1001	)
#define ACTOR_PLAYER_BULLET				uint32_t(	1002	)
															
#define ACTOR_CREEP_TANK				uint32_t(	2001	)
#define ACTOR_CREEP_BULLET				uint32_t(	2002	)
															
#define ACTOR_TURRET					uint32_t(	3001	)
#define ACTOR_TURRET_BULLET				uint32_t(	3002	)
															
#define ACTOR_HEADQUARTER				uint32_t(	4001	)
#define ACTOR_FACTORY					uint32_t(	4002	)
															
#define ACTOR_REPAIR_KIT				uint32_t(	5001	)
#define ACTOR_POWER_UP					uint32_t(	5002	)
															
#define ACTOR_BOUND						uint32_t(	6001	)
#define ACTOR_WALL						uint32_t(	6002	)
#define ACTOR_TREE						uint32_t(	6003	)
#define ACTOR_WATER						uint32_t(	6004	)
#pragma endregion

#pragma region FILTER_DEFINITION
#define FILTER_NON_COLLIDABLE			uint16_t(	0x0001	)
#define FILTER_PLAYER_TANK				uint16_t(	0x0002	)
#define FILTER_CREEP_TANK				uint16_t(	0x0004	)
#define FILTER_BULLET					uint16_t(	0x0008	)
#define FILTER_STRUCTURE				uint16_t(	0x0010	)
#define FILTER_WALL						uint16_t(	0x0020	)
#define FILTER_WATER					uint16_t(	0x0040	)
#define FILTER_TREE						uint16_t(	0x0080	)
#define FILTER_PICK_UP					uint16_t(	0x0100	)
#pragma endregion

class World : public b2ContactListener {
protected:
	pGame game;

public:
	b2Vec2 gravity;
	b2World* physics_world = nullptr;

	uint32_t game_object_id = 1000;
	std::map<std::string, uint32_t> dictionary;
	std::map<uint32_t, pGameObject> game_objects;
	std::map<uint32_t, std::vector<pCommand>> commands;

	uint32_t latest_tick = 0;
	uint32_t server_tick = 0;

	bool just_got_game_state = false;
	uint32_t tick_per_game_state = 8;

	World(pGame game);
	~World();

	void HandleInput(uint32_t tick);
	void Step(uint32_t tick, float elapsed);
	void TrimCommands(uint32_t threshold);

	b2World* GetPhysics();
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
};
typedef World* pWorld;

#endif // !__CLIENT_WORLD_H__
