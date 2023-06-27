#include "server/actor/power_up.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pPowerUp CPowerUp::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, nlohmann::json& components_data
		) {
			if (world->dictionary.find("name") != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CPowerUp>(game, world, id, name);
			world->dictionary[name] = id;

			auto power_up = static_cast<pPowerUp>(world->game_objects[id].get());
			power_up->LoadComponents(components_data);

			world->render_queue.emplace(power_up->layer, id);

			return power_up;
		}

		CPowerUp::CPowerUp(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CPowerUp(game, world, id, name) {
		}

		CPowerUp::~CPowerUp() {
		}

	}
}
