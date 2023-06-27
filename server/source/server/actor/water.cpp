#include "server/actor/water.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pWater CWater::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, nlohmann::json& components_data
		) {
			if (world->dictionary.find("name") != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CWater>(game, world, id, name);
			world->dictionary[name] = id;

			auto water = static_cast<pWater>(world->game_objects[id].get());
			water->LoadComponents(components_data);

			world->render_queue.emplace(water->layer, id);

			return water;
		}

		CWater::CWater(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CWater(game, world, id, name) {
		}

		CWater::~CWater() {
		}

	}
}
