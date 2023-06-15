#include "server/actor/turret.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pTurret CTurret::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("name");
			world->game_objects[id] = std::make_unique<CTurret>(game, world, id, name);
			world->dictionary[name] = id;

			pTurret turret = static_cast<pTurret>(world->game_objects[id].get());

			auto& physics_data = data.at("physics");
			turret->CreatePhysics(physics_data);

			std::string resource_path = data.at("resource_path");
			turret->SetResourcePath(resource_path);
			turret->LoadResource();

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
