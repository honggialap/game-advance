#include "server/actor/repair_kit.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pRepairKit CRepairKit::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, nlohmann::json& components_data
		) {
			if (world->dictionary.find("name") != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CRepairKit>(game, world, id, name);
			world->dictionary[name] = id;

			auto repairt_kit = static_cast<pRepairKit>(world->game_objects[id].get());
			repairt_kit->LoadComponents(components_data);

			world->render_queue.emplace(repairt_kit->layer, id);

			return repairt_kit;
		}

		CRepairKit::CRepairKit(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CRepairKit(game, world, id, name) {
		}

		CRepairKit::~CRepairKit() {
		}

	}
}
