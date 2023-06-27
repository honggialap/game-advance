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

		void CWorld::HandleInput(uint32_t tick) {
			for (auto& game_object_container : game_objects) {
				pGameObject game_object = game_object_container.second.get();
				auto input_handler = dynamic_cast<NSComponent::pInputHandler>(game_object);
				if (input_handler) {
					input_handler->HandleInput(tick);
				}
			}
		}

		void CWorld::Step(uint32_t tick, float elapsed) {
			if (commands.find(tick) != commands.end()) {
				auto& commands_at_tick = commands.at(tick);
				for (auto& command : commands_at_tick) {
					pGameObject game_object = game_objects[command->game_object_id].get();
					auto commandable = dynamic_cast<NSComponent::pCommandable>(game_object);
					if (commandable) {
						commandable->ExecuteCommand(command.get());
					}
				}
			}

			for (auto& game_object_container : game_objects) {
				pGameObject game_object = game_object_container.second.get();
				auto updatable = dynamic_cast<NSComponent::pUpdatable>(game_object);
				if (updatable) {
					if (updatable->IsActive()) {
						updatable->Update(elapsed);
					}
				}
			}
			physics_world->Step(elapsed, 8, 3);
		}

		void CWorld::Render(sf::RenderWindow& window) {
			for (auto& render_queue_element : render_queue) {
				pGameObject game_object = game_objects[render_queue_element.second].get();
				auto renderable = dynamic_cast<NSComponent::pRenderable>(game_object);
				if (renderable) {
					if (renderable->IsVisible()) {
						renderable->Render(window);
					}
				}
			}
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

		void CWorld::TrimCommands(uint32_t from, uint32_t to) {
			for (uint32_t erasing_tick = to;
				erasing_tick > from;
				erasing_tick--) {
				commands.erase(erasing_tick);
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
				pGameObject game_object = game_object_container.second.get();
				auto recordable = dynamic_cast<NSComponent::pRecordable>(game_object);
				if (recordable) {
					recordable->Serialize(tick);
				}
			}
		}

		void CWorld::Deserialize(uint32_t tick) {
			auto& records_container = records[tick];
			for (auto& record : records_container) {
				pGameObject game_object = game_objects[record->game_object_id].get();
				auto recordable = dynamic_cast<NSComponent::pRecordable>(game_object);
				if (recordable) {
					recordable->Deserialize(record.get());
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
