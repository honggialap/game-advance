#include "engine/core/world.h"
#include "engine/core/game.h"

namespace NSEngine {
	namespace NSCore {

		CWorld::CWorld(pGame game)
			: game(game) {
			gravity = b2Vec2(0, 0);
			physics_world = new b2World(gravity);
			physics_world->SetContactListener(this);
		}

		CWorld::~CWorld() {
			if (game) {
				game = nullptr;
			}

			if (physics_world) {
				delete physics_world;
				physics_world = nullptr;
			}
		}

		void CWorld::Load(nlohmann::json& data) {
			/*
			if (data.contains("game_master")) {
				auto& game_master = data.at("game_master");
				GameMaster::Create(game, this, game_master);
			}

			if (data.contains("player_tanks")) {
				auto& player_tanks = data.at("player_tanks");
				for (auto& player_tank : player_tanks) {
					PlayerTank::Create(game, this, player_tank);

					if (player_tank.contains("bullets")) {
						auto& bullets = player_tank.at("bullets");
						for (auto& bullet : bullets) {
							PlayerBullet::Create(game, this, bullet);
						}
					}
				}
			}

			if (data.contains("headquarters")) {
				auto& headquarters = data.at("headquarters");
				for (auto& headquarter : headquarters) {
					Headquarter::Create(game, this, headquarter);
				}
			}

			if (data.contains("factories")) {
				auto& factories = data.at("factories");
				for (auto& factory : factories) {
					Factory::Create(game, this, factory);

					if (factories.contains("creep_tanks")) {
						auto& creep_tanks = factory.at("creep_tanks");
						for (auto& creep_tank : creep_tanks) {
							CreepTank::Create(game, this, creep_tank);

							if (creep_tank.contains("bullets")) {
								auto& bullets = creep_tank.at("bullets");
								for (auto& bullet : bullets) {
									CreepBullet::Create(game, this, bullet);
								}
							}
						}
					}
				}
			}

			if (data.contains("turrets")) {
				auto& turrets = data.at("turrets");
				for (auto& turret : turrets) {
					Turret::Create(game, this, turret);

					if (turret.contains("bullets")) {
						auto& bullets = turret.at("bullets");
						for (auto& bullet : bullets) {
							TurretBullet::Create(game, this, bullet);
						}
					}
				}
			}

			if (data.contains("bounds")) {
				auto& bounds = data.at("bounds");
				for (auto& bound : bounds) {
					Bound::Create(game, this, bound);
				}
			}

			if (data.contains("walls")) {
				auto& walls = data.at("walls");
				for (auto& wall : walls) {
					Wall::Create(game, this, wall);
				}
			}

			if (data.contains("waters")) {
				auto& waters = data.at("waters");
				for (auto& water : waters) {
					Water::Create(game, this, water);
				}
			}

			if (data.contains("trees")) {
				auto& trees = data.at("trees");
				for (auto& tree : trees) {
					Tree::Create(game, this, tree);
				}
			}

			if (data.contains("repair_kits")) {
				auto& repair_kits = data.at("repair_kits");
				for (auto& repair_kit : repair_kits) {
					RepairKit::Create(game, this, repair_kit);
				}
			}

			if (data.contains("power_ups")) {
				auto& power_ups = data.at("power_ups");
				for (auto& power_up : power_ups) {
					PowerUp::Create(game, this, power_up);
				}
			}
			*/
		}

		void CWorld::Unload() {
		}

		void CWorld::HandleInput(uint32_t tick) {
			for (auto& game_object_container : game_objects) {
				auto game_object = game_object_container.second.get();
				if (dynamic_cast<NSComponent::pPlayerControl>(game_object)) {
					dynamic_cast<NSComponent::pPlayerControl>(game_object)->HandleInput(tick);
				}
			}
		}

		void CWorld::Step(uint32_t tick, float elapsed) {
			if (commands.find(tick) != commands.end()) {
				auto& commands_at_tick = commands.at(tick);
				for (auto& command : commands_at_tick) {
					auto game_object = game_objects[command->game_object_id].get();
					if (dynamic_cast<NSComponent::pCommandable>(game_object)) {
						dynamic_cast<NSComponent::pCommandable>(game_object)->ExecuteCommand(command.get());
					}
				}
			}

			for (auto& game_object_container : game_objects) {
				auto game_object = game_object_container.second.get();
				if (dynamic_cast<NSComponent::pUpdatable>(game_object)) {
					dynamic_cast<NSComponent::pUpdatable>(game_object)->Update(elapsed);
				}
			}
			physics_world->Step(elapsed, 8, 3);
		}

		void CWorld::TrimCommands(uint32_t threshold) {
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

		void CWorld::TrimRecords(uint32_t threshold) {
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

		void CWorld::TrimRecords(uint32_t from, uint32_t to) {
			for (uint32_t erasing_tick = to;
				erasing_tick > from;
				erasing_tick--) {
				records.erase(erasing_tick);
			}
		}

		void CWorld::Serialize(uint32_t tick) {
			for (auto& game_object_container : game_objects) {
				auto game_object = game_object_container.second.get();
				if (dynamic_cast<NSComponent::pRecordable>(game_object)) {
					dynamic_cast<NSComponent::pRecordable>(game_object)->Serialize(tick);
				}
			}
		}

		void CWorld::Deserialize(uint32_t tick) {
			auto& records_container = records[tick];
			for (auto& record : records_container) {
				auto game_object = game_objects[record->game_object_id].get();
				if (dynamic_cast<NSComponent::pRecordable>(game_object)) {
					dynamic_cast<NSComponent::pRecordable>(game_object)->Deserialize(record.get());
				}
			}
		}

		b2World* CWorld::GetPhysics() {
			return physics_world;
		}

		void CWorld::BeginContact(b2Contact* contact) {
			auto dataA = (void*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
			auto dataB = (void*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
			if (dataA && dataB) {
				auto objectA = static_cast<NSComponent::pPhysics>(dataA);
				auto objectB = static_cast<NSComponent::pPhysics>(dataB);
				objectA->OnCollisionEnter(objectB);
				objectB->OnCollisionEnter(objectA);
			}
		}

		void CWorld::EndContact(b2Contact* contact) {
			auto dataA = (void*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
			auto dataB = (void*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
			if (dataA && dataB) {
				auto objectA = static_cast<NSComponent::pPhysics>(dataA);
				auto objectB = static_cast<NSComponent::pPhysics>(dataB);
				objectA->OnCollisionExit(objectB);
				objectB->OnCollisionExit(objectA);
			}
		}

	}
}
