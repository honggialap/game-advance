#include "client/actor/terrain/ice.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {

		pIce CIce::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
		) {
			if (world->dictionary.find("name") != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CIce>(game, world, id, name);
			world->dictionary[name] = id;

			return static_cast<pIce>(world->game_objects[id].get());
		}

		CIce::CIce(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CIce(game, world, id, name) {
		}

		CIce::~CIce() {
		}

	}
}