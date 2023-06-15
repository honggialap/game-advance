#include "client/actor/tree.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {

		pTree CTree::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
		) {
			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CTree>(game, world, id, name);
			world->dictionary[name] = id;

			pTree tree = static_cast<pTree>(world->game_objects[id].get());
			return tree;
		}

		CTree::CTree(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CTree(game, world, id, name) {
		}

		CTree::~CTree() {
		}

	}
}
