#include "server/actor/turret.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pTurret CTurret::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, nlohmann::json& components_data
		) {
			if (world->dictionary.find("name") != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CTurret>(game, world, id, name);
			world->dictionary[name] = id;

			auto turret = static_cast<pTurret>(world->game_objects[id].get());
			turret->LoadComponents(components_data);

			world->render_queue.emplace(turret->layer, id);

			return turret;
		}

		CTurret::CTurret(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CTurret(game, world, id, name) {
		}

		CTurret::~CTurret() {
		}

	}
}
