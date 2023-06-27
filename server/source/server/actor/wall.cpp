#include "server/actor/wall.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pWall CWall::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, nlohmann::json& components_data
		) {
			if (world->dictionary.find("name") != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CWall>(game, world, id, name);
			world->dictionary[name] = id;

			auto wall = static_cast<pWall>(world->game_objects[id].get());
			wall->LoadComponents(components_data);

			world->render_queue.emplace(wall->layer, id);

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
