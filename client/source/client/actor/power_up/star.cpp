#include "client/actor/power_up/star.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {

		pStar CStar::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
		) {
			if (world->dictionary.find("name") != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CStar>(game, world, id, name);
			world->dictionary[name] = id;

			return static_cast<pStar>(world->game_objects[id].get());
		}

		CStar::CStar(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CStar(game, world, id, name) {
		}

		CStar::~CStar() {
		}

	}
}
