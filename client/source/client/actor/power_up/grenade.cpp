#include "client/actor/power_up/grenade.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {

		pGrenade CGrenade::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
		) {
			if (world->dictionary.find("name") != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CGrenade>(game, world, id, name);
			world->dictionary[name] = id;

			return static_cast<pGrenade>(world->game_objects[id].get());
		}

		CGrenade::CGrenade(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CGrenade(game, world, id, name) {
		}

		CGrenade::~CGrenade() {
		}

	}
}
