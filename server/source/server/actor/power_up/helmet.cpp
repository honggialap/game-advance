#include "server/actor/power_up/helmet.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pHelmet CHelmet::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, nlohmann::json& components_data
		) {
			if (world->dictionary.find("name") != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CHelmet>(game, world, id, name);
			world->dictionary[name] = id;

			auto game_object = static_cast<pHelmet>(world->game_objects[id].get());
			game_object->LoadComponents(components_data);

			world->render_queue.emplace(game_object->layer, id);

			return game_object;
		}

		CHelmet::CHelmet(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CHelmet(game, world, id, name) {
		}

		CHelmet::~CHelmet() {
		}

	}
}