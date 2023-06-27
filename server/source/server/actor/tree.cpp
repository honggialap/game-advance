#include "server/actor/tree.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pTree CTree::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, nlohmann::json& components_data
		) {
			if (world->dictionary.find("name") != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CTree>(game, world, id, name);
			world->dictionary[name] = id;

			auto tree = static_cast<pTree>(world->game_objects[id].get());
			tree->LoadComponents(components_data);

			world->render_queue.emplace(tree->layer, id);

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
