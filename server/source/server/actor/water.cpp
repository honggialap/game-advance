#include "server/actor/water.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pWater CWater::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("name");
			world->game_objects[id] = std::make_unique<CWater>(game, world, id, name);
			world->dictionary[name] = id;

			pWater water = static_cast<pWater>(world->game_objects[id].get());

			auto& physics_data = data.at("physics");
			water->CreatePhysics(physics_data);

			std::string resource_path = data.at("resource_path");
			water->SetResourcePath(resource_path);
			water->LoadResource();

			return water;
		}

		CWater::CWater(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CWater(game, world, id, name) {
		}

		CWater::~CWater() {
		}

	}
}
