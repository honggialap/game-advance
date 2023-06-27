#include "server/actor/headquarter.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pHeadquarter CHeadquarter::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, nlohmann::json& components_data
		) {
			if (world->dictionary.find("name") != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CHeadquarter>(game, world, id, name);
			world->dictionary[name] = id;

			auto headquarter = static_cast<pHeadquarter>(world->game_objects[id].get());
			headquarter->LoadComponents(components_data);

			world->render_queue.emplace(headquarter->layer, id);

			return headquarter;
		}

		CHeadquarter::CHeadquarter(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world) 
			, NSEngine::NSActor::CHeadquarter(game, world, id, name) {
		}

		CHeadquarter::~CHeadquarter() {
		}

	}
}