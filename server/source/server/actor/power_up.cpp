#include "server/actor/power_up.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pPowerUp CPowerUp::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("name");
			world->game_objects[id] = std::make_unique<CPowerUp>(game, world, id, name);
			world->dictionary[name] = id;

			pPowerUp power_up = static_cast<pPowerUp>(world->game_objects[id].get());

			auto& physics_data = data.at("physics");
			power_up->CreatePhysics(physics_data);

			std::string resource_path = data.at("resource_path");
			power_up->SetResourcePath(resource_path);
			power_up->LoadResource();

			return power_up;
		}

		CPowerUp::CPowerUp(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CPowerUp(game, world, id, name) {
		}

		CPowerUp::~CPowerUp() {
		}

	}
}
