#include "server/actor/effect/impact.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pImpact CImpact::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, nlohmann::json& components_data
		) {
			if (world->dictionary.find("name") != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CImpact>(game, world, id, name);
			world->dictionary[name] = id;

			auto game_object = static_cast<pImpact>(world->game_objects[id].get());
			game_object->LoadComponents(components_data);

			world->render_queue.emplace(game_object->layer, id);

			return game_object;
		}

		CImpact::CImpact(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CImpact(game, world, id, name) {
		}

		CImpact::~CImpact() {
		}

	}
}