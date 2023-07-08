#include "client/actor/tank/bullet.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {

		pBullet CBullet::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
		) {
			if (world->dictionary.find(name) != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CBullet>(game, world, id, name);
			world->dictionary[name] = id;

			return static_cast<pBullet>(world->game_objects[id].get());
		}

		CBullet::CBullet(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSActor::CBullet(game, world, id, name)
			, NSClient::NSCore::CGameObject(game, world) {
		}

		CBullet::~CBullet() {
		}

	}
}