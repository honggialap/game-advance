#include "client/actor/player_bullet.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {

		pPlayerBullet CPlayerBullet::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
		) {
			if (world->dictionary.find(name) != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CPlayerBullet>(game, world, id, name);
			world->dictionary[name] = id;

			return static_cast<pPlayerBullet>(world->game_objects[id].get());
		}

		CPlayerBullet::CPlayerBullet(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CPlayerBullet(game, world, id, name) {
		}

		CPlayerBullet::~CPlayerBullet() {
		}

	}
}
