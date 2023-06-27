#include "server/actor/player_tank.h"
#include "server/core/game.h"
#include "server/core/world.h"

#include "server/actor/wall.h"

namespace NSServer {
	namespace NSActor {

		pPlayerTank CPlayerTank::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, nlohmann::json& components_data
		) {
			if (world->dictionary.find(name) != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CPlayerTank>(game, world, id, name);
			world->dictionary[name] = id;

			auto player_tank = static_cast<pPlayerTank>(world->game_objects[id].get());
			player_tank->LoadComponents(components_data);

			world->render_queue.emplace(player_tank->layer, id);

			return player_tank;
		}

		CPlayerTank::CPlayerTank(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CPlayerTank(game, world, id, name) {
		}

		CPlayerTank::~CPlayerTank() {
		}

	}
}
