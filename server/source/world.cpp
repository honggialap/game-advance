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


World::World(pGame game) {
	this->game = game;

	gravity = b2Vec2(0, 0);
	physics_world = new b2World(gravity);
	physics_world->SetContactListener(this);
}

World::~World() {
	if (game) {
		game = nullptr;
	}

	if (physics_world) {
		delete physics_world;
		physics_world = nullptr;
	}
}

void World::Load(nlohmann::json& data) {

	auto& game_master = data.at("game_master");
	GameMaster::Create(game, this, game_master);

	auto& player_tanks = data.at("player_tanks");
	for (auto& player_tank : player_tanks) {
		PlayerTank::Create(game, this, player_tank);

		auto& bullets = player_tank.at("bullets");
		for (auto& bullet : bullets) {
			PlayerBullet::Create(game, this, bullet);
		}
	}

	auto& headquarters = data.at("headquarters");
	for (auto& headquarter : headquarters) {
		Headquarter::Create(game, this, headquarter);
	}

	auto& factories = data.at("factories");
	for (auto& factory : factories) {
		Factory::Create(game, this, factory);

		auto& creep_tanks = factory.at("creep_tanks");
		for (auto& creep_tank : creep_tanks) {
			CreepTank::Create(game, this, creep_tank);

			auto& bullets = creep_tank.at("bullets");
			for (auto& bullet : bullets) {
				CreepBullet::Create(game, this, bullet);
			}
		}
	}

	auto& turrets = data.at("turrets");
	for (auto& turret : turrets) {
		Turret::Create(game, this, turret);

		auto& bullets = turret.at("bullets");
		for (auto& bullet : bullets) {
			TurretBullet::Create(game, this, bullet);
		}
	}

	auto& bounds = data.at("bounds");
	for (auto& bound : bounds) {
		Bound::Create(game, this, bound);
	}

	auto& walls = data.at("walls");
	for (auto& wall : walls) {
		Wall::Create(game, this, wall);
	}

	auto& waters = data.at("waters");
	for (auto& water : waters) {
		Water::Create(game, this, water);
	}

	auto& trees = data.at("trees");
	for (auto& tree : trees) {
		Tree::Create(game, this, tree);
	}

	auto& repair_kits = data.at("repair_kits");
	for (auto& repair_kit : repair_kits) {
		RepairKit::Create(game, this, repair_kit);
	}

	auto& power_ups = data.at("power_ups");
	for (auto& power_up : power_ups) {
		PowerUp::Create(game, this, power_up);
	}
}

void World::Unload() {
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
		erasing_tick > from;
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
