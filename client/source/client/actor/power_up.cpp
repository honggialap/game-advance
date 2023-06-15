#include "client/actor/power_up.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {

		pPowerUp CPowerUp::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
		) {
			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CPowerUp>(game, world, id, name);
			world->dictionary[name] = id;

			pPowerUp power_up = static_cast<pPowerUp>(world->game_objects[id].get());
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
