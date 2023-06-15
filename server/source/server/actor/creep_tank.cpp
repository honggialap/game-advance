#include "server/actor/creep_tank.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pCreepTank CCreepTank::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("name");
			world->game_objects[id] = std::make_unique<CCreepTank>(game, world, id, name);
			world->dictionary[name] = id;

			pCreepTank creep_tank = static_cast<pCreepTank>(world->game_objects[id].get());

			auto& physics_data = data.at("physics");
			creep_tank->CreatePhysics(physics_data);

			std::string resource_path = data.at("resource_path");
			creep_tank->SetResourcePath(resource_path);
			creep_tank->LoadResource();

			return creep_tank;
		}

		CCreepTank::CCreepTank(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CCreepTank(game, world, id, name) {
		}

		CCreepTank::~CCreepTank() {
		}

		void CCreepTank::HandleInput(uint32_t tick) {
		}

	}
}
