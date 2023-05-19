#include "world.h"
#include "game.h"

#include "game_master.h"
#include "player_tank.h"
#include "player_bullet.h"
#include "creep_tank.h"
#include "creep_bullet.h"
#include "turret.h"
#include "turret_bullet.h"
#include "headquarter.h"
#include "factory.h"
#include "repair_kit.h"
#include "power_up.h"
#include "bound.h"
#include "wall.h"
#include "tree.h"
#include "water.h"

World::World() {
	gravity = b2Vec2(0, 0);
	physics_world = new b2World(gravity);
	physics_world->SetContactListener(this);
}

World::~World() {
	if (physics_world) {
		delete physics_world;
		physics_world = nullptr;
	}
}

void World::HandleInput(uint32_t tick) {
	for (auto& game_object_container : game_objects) {
		game_object_container.second->HandleInput(
			tick
		);
	}
}

void World::Step(uint32_t tick, float elapsed) {
	if (commands.find(tick) != commands.end()) {
		auto& commands_at_tick = commands.at(tick);
		for (auto& command : commands_at_tick) {
			game_objects[
				command->game_object_id
			]->ExecuteCommand(command.get());
		}
	}

	for (auto& game_object_container : game_objects) {
		game_object_container.second->Update(elapsed);
	}
	physics_world->Step(elapsed, 8, 3);
}

void World::TrimCommands(uint32_t threshold) {
	if (!commands.empty() && latest_tick > threshold) {
		while (
			!commands.empty()
			&& commands.begin()->first < latest_tick - threshold
			) {
			auto erasing_tick = commands.begin()->first;
			commands.erase(erasing_tick);
		}
	}
}

b2World* World::GetPhysics() {
	return physics_world;
}

void World::BeginContact(b2Contact* contact) {
	auto dataA = (void*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	auto dataB = (void*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
	if (dataA && dataB) {
		auto objectA = static_cast<GameObject*>(dataA);
		auto objectB = static_cast<GameObject*>(dataB);
		objectA->OnCollisionEnter(objectB);
		objectB->OnCollisionEnter(objectA);
	}
}

void World::EndContact(b2Contact* contact) {
	auto dataA = (void*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	auto dataB = (void*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
	if (dataA && dataB) {
		auto objectA = static_cast<GameObject*>(dataA);
		auto objectB = static_cast<GameObject*>(dataB);
		objectA->OnCollisionExit(objectB);
		objectB->OnCollisionExit(objectA);
	}
}
