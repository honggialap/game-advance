#include "server/actor/tank/power_tank.h"
#include "server/core/game.h"
#include "server/core/world.h"

#include "server/actor/terrain/brick.h"

namespace NSServer {
	namespace NSActor {

		pPowerTank CPowerTank::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, nlohmann::json& components_data
		) {
			if (world->dictionary.find(name) != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CPowerTank>(game, world, id, name);
			world->dictionary[name] = id;

			auto game_object = static_cast<pPowerTank>(world->game_objects[id].get());
			game_object->LoadComponents(components_data);

			world->render_queue.emplace(game_object->layer, id);

			return game_object;
		}

		CPowerTank::CPowerTank(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CPowerTank(game, world, id, name) {
		}

		CPowerTank::~CPowerTank() {
		}

		void CPowerTank::HandleInput(uint32_t tick) {
		}

	}
}
