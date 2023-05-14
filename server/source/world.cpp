#include "world.h"
#include "game.h"
#include "tank.h"
#include "bullet.h"
#include "wall.h"

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

GameObject* World::CreateGameObject(
	Game* game,
	uint32_t game_object_type,
	float position_x,
	float position_y
) {
	GameObject* game_object = nullptr;
	switch (game_object_type) {
	case ACTOR_TYPE_TANK: {
		game_objects[game_object_id] = std::make_unique<Tank>(game, this, game_object_id, game_object_type);
		GameObject* game_object = game_objects[game_object_id].get();
		game_object->Load("");
		game_object->SetPosition(position_x, position_y);
		game_object_id += 1;
		return game_object;
	}

	case ACTOR_TYPE_BULLET: {
		game_objects[game_object_id] = std::make_unique<Bullet>(game, this, game_object_id, game_object_type);
		GameObject* game_object = game_objects[game_object_id].get();
		game_object->Load("");
		game_object->SetPosition(position_x, position_y);
		game_object_id += 1;
		return game_object;
	}

	case ACTOR_TYPE_WALL: {
		game_objects[game_object_id] = std::make_unique<Wall>(game, this, game_object_id, game_object_type);
		GameObject* game_object = game_objects[game_object_id].get();
		game_object->Load("");
		game_object->SetPosition(position_x, position_y);
		game_object_id += 1;
		return game_object;
	}

	default:
		return game_object;
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

void World::TrimRecords(uint32_t threshold) {
	if (!records.empty() && latest_tick > threshold) {
		while (
			!records.empty()
			&& records.begin()->first < latest_tick - threshold
			) {
			auto erasing_tick = records.begin()->first;
			records.erase(erasing_tick);
		}
	}
}

void World::TrimRecords(uint32_t from, uint32_t to) {
	for (uint32_t erasing_tick = to;
		erasing_tick >= from;
		erasing_tick--) {
		records.erase(erasing_tick);
	}
}

void World::Serialize(uint32_t tick) {
	for (auto& game_object_container : game_objects) {
		game_object_container.second->Serialize(tick);
	}
}

void World::Deserialize(uint32_t tick) {
	auto& records_container = records[tick];
	for (auto& record : records_container) {
		game_objects[record->game_object_id]->Deserialize(record.get());
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
