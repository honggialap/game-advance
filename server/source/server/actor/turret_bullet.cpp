#include "server/actor/turret_bullet.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pTurretBullet CTurretBullet::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("name");
			world->game_objects[id] = std::make_unique<CTurretBullet>(game, world, id, name);
			world->dictionary[name] = id;

			pTurretBullet turret_bullet = static_cast<pTurretBullet>(world->game_objects[id].get());

			auto& physics_data = data.at("physics");
			turret_bullet->CreatePhysics(physics_data);

			std::string resource_path = data.at("resource_path");
			turret_bullet->SetResourcePath(resource_path);
			turret_bullet->LoadResource();

			return turret_bullet;
		}

		CTurretBullet::CTurretBullet(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CTurretBullet(game, world, id, name) {
		}

		CTurretBullet::~CTurretBullet() {
		}

	}
}
