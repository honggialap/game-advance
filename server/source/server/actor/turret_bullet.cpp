#include "server/actor/turret_bullet.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pTurretBullet CTurretBullet::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, nlohmann::json& components_data
		) {
			if (world->dictionary.find("name") != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CTurretBullet>(game, world, id, name);
			world->dictionary[name] = id;

			auto turret_bullet = static_cast<pTurretBullet>(world->game_objects[id].get());
			turret_bullet->LoadComponents(components_data);

			world->render_queue.emplace(turret_bullet->layer, id);

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
