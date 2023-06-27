#include "server/actor/creep_tank.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pCreepTank CCreepTank::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, nlohmann::json& components_data
		) {
			if (world->dictionary.find("name") != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CCreepTank>(game, world, id, name);
			world->dictionary[name] = id;

			auto creep_tank = static_cast<pCreepTank>(world->game_objects[id].get());
			creep_tank->LoadComponents(components_data);

			world->render_queue.emplace(creep_tank->layer, id);

			return creep_tank;
		}

		CCreepTank::CCreepTank(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CCreepTank(game, world, id, name) {
		}

		CCreepTank::~CCreepTank() {
		}

		void CCreepTank::HandleInput(uint32_t tick) {
		}

	}
}
