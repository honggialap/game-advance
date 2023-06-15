#include "server/actor/tree.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pTree CTree::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("name");
			world->game_objects[id] = std::make_unique<CTree>(game, world, id, name);
			world->dictionary[name] = id;

			pTree tree = static_cast<pTree>(world->game_objects[id].get());

			auto& physics_data = data.at("physics");
			tree->CreatePhysics(physics_data);

			std::string resource_path = data.at("resource_path");
			tree->SetResourcePath(resource_path);
			tree->LoadResource();

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
