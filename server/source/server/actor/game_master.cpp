#include "server/actor/game_master.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pGameMaster CGameMaster::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("name");

			world->game_objects[id] = std::make_unique<CGameMaster>(game, world, id, name);
			world->dictionary[name] = id;
			pGameMaster game_master = static_cast<pGameMaster>(world->game_objects[id].get());

			return game_master;
		}

		CGameMaster::CGameMaster(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CGameMaster(game, world, id, name) {
		}

		CGameMaster::~CGameMaster() {
		}

	}
}
