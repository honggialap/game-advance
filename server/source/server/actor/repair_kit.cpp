#include "server/actor/repair_kit.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pRepairKit CRepairKit::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("name");
			world->game_objects[id] = std::make_unique<CRepairKit>(game, world, id, name);
			world->dictionary[name] = id;

			pRepairKit repair_kit = static_cast<pRepairKit>(world->game_objects[id].get());

			auto& physics_data = data.at("physics");
			repair_kit->CreatePhysics(physics_data);

			std::string resource_path = data.at("resource_path");
			repair_kit->SetResourcePath(resource_path);
			repair_kit->LoadResource();

			return repair_kit;
		}

		CRepairKit::CRepairKit(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CRepairKit(game, world, id, name) {
		}

		CRepairKit::~CRepairKit() {
		}

	}
}
