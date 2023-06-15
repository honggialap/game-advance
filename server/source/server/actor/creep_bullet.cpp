#include "server/actor/creep_bullet.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pCreepBullet CCreepBullet::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("name");
			world->game_objects[id] = std::make_unique<CCreepBullet>(game, world, id, name);
			world->dictionary[name] = id;

			pCreepBullet creep_bullet = static_cast<pCreepBullet>(world->game_objects[id].get());

			auto& physics_data = data.at("physics");
			creep_bullet->CreatePhysics(physics_data);

			std::string resource_path = data.at("resource_path");
			creep_bullet->SetResourcePath(resource_path);
			creep_bullet->LoadResource();

			return creep_bullet;
		}

		CCreepBullet::CCreepBullet(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSActor::CCreepBullet(game, world, id, name)
			, NSServer::NSCore::CGameObject(game, world) {
		}

		CCreepBullet::~CCreepBullet() {
		}

	}
}
