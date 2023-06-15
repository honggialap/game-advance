#include "client/actor/wall.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {

		pWall CWall::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
		) {
			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CWall>(game, world, id, name);
			world->dictionary[name] = id;

			pWall wall = static_cast<pWall>(world->game_objects[id].get());
			return wall;
		}

		CWall::CWall(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world) 
			, NSEngine::NSActor::CWall(game, world, id, name) {
		}

		CWall::~CWall() {
		}

	}
}
