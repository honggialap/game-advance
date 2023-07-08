#include "server/actor/game_master.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pGameMaster CGameMaster::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, nlohmann::json& components_data
		) {
			if (world->dictionary.find(name) != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CGameMaster>(game, world, id, name);
			world->dictionary[name] = id;

			auto game_object = static_cast<pGameMaster>(world->game_objects[id].get());
			game_object->LoadComponents(components_data);

			world->render_queue.emplace(game_object->layer, id);

			return game_object;
		}

		CGameMaster::CGameMaster(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CGameMaster(game, world, id, name) {
		}

		CGameMaster::~CGameMaster() {
		}

		void CGameMaster::Update(float elapsed) {
			if (!started) {
				started = true;

				SpawnPlayerTank(1);
				SpawnPlayerTank(2);

				SpawnEnemyTank(0, 0);
				SpawnEnemyTank(1, 1);
				SpawnEnemyTank(2, 2);
				
				//SpawnPowerUp(NSEngine::STAR, 4);
			}
		}

		void CGameMaster::PackLoadPacket(NSEngine::NSNetworks::CPacket* packet) {
			NSEngine::NSCore::CGameObject::PackLoadPacket(packet);
		}

	}
}
