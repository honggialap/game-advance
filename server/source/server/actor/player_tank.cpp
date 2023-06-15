#include "server/actor/player_tank.h"
#include "server/core/game.h"
#include "server/core/world.h"

#include "server/actor/wall.h"

namespace NSServer {
	namespace NSActor {

		pPlayerTank CPlayerTank::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("name");

			world->game_objects[id] = std::make_unique<CPlayerTank>(game, world, id, name);
			world->dictionary[name] = id;
			pPlayerTank player_tank = static_cast<pPlayerTank>(world->game_objects[id].get());

			auto& physics_data = data.at("physics");
			player_tank->CreatePhysics(physics_data);

			std::string resource_path = data.at("resource_path");
			player_tank->SetResourcePath(resource_path);
			player_tank->LoadResource();

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
