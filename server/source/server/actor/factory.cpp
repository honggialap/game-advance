#include "server/actor/factory.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pFactory CFactory::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, nlohmann::json& components_data
		) {
			if (world->dictionary.find("name") != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CFactory>(game, world, id, name);
			world->dictionary[name] = id;

			auto factory = static_cast<pFactory>(world->game_objects[id].get());
			factory->LoadComponents(components_data);

			world->render_queue.emplace(factory->layer, id);

			return factory;
		}

		CFactory::CFactory(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CFactory(game, world, id, name) {
		}

		CFactory::~CFactory() {
		}

	}
}
