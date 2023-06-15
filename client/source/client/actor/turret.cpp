#include "client/actor/turret.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {
		
		pTurret CTurret::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
		) {
			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CTurret>(game, world, id, name);
			world->dictionary[name] = id;

			pTurret turret = static_cast<pTurret>(world->game_objects[id].get());
			return turret;
		}

		CTurret::CTurret(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CTurret(game, world, id, name) {
		}

		CTurret::~CTurret() {
		}

	}
}
