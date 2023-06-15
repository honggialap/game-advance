#include "client/actor/water.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {

		pWater CWater::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
		) {
			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CWater>(game, world, id, name);
			world->dictionary[name] = id;

			pWater water = static_cast<pWater>(world->game_objects[id].get());
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
