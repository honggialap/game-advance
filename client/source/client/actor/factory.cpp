#include "client/actor/factory.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {

		pFactory CFactory::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
		) {
			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CFactory>(game, world, id, name);
			world->dictionary[name] = id;

			pFactory factory = static_cast<pFactory>(world->game_objects[id].get());
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
