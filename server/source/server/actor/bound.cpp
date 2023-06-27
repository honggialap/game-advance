#include "server/actor/bound.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pBound CBound::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, nlohmann::json& components_data
		) {
			if (world->dictionary.find("name") != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CBound>(game, world, id, name);
			world->dictionary[name] = id;

			auto bound = static_cast<pBound>(world->game_objects[id].get());
			bound->LoadComponents(components_data);

			return bound;
		}

		CBound::CBound(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world) 
			, NSEngine::NSActor::CBound(game, world, id, name) {
		}

		CBound::~CBound() {
		}
	
	}
}