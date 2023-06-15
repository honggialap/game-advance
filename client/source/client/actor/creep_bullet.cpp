#include "client/actor/creep_bullet.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {

		pCreepBullet CCreepBullet::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
		) {
			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CCreepBullet>(game, world, id, name);
			world->dictionary[name] = id;

			pCreepBullet creep_bullet = static_cast<pCreepBullet>(world->game_objects[id].get());
			return creep_bullet;
		}
		
		CCreepBullet::CCreepBullet(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSActor::CCreepBullet(game, world, id, name)
			, NSClient::NSCore::CGameObject(game, world) {
		}

		CCreepBullet::~CCreepBullet() {
		}

	}
}