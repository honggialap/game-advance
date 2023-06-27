#include "server/actor/creep_bullet.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pCreepBullet CCreepBullet::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, nlohmann::json& components_data
		) {
			if (world->dictionary.find("name") != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CCreepBullet>(game, world, id, name);
			world->dictionary[name] = id;

			auto creep_bullet = static_cast<pCreepBullet>(world->game_objects[id].get());
			creep_bullet->LoadComponents(components_data);
			
			world->render_queue.emplace(creep_bullet->layer, id);

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
