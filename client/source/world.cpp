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
