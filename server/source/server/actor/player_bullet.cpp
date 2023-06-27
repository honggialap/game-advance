#include "server/actor/player_bullet.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pPlayerBullet CPlayerBullet::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, nlohmann::json& components_data
		) {
			if (world->dictionary.find(name) != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CPlayerBullet>(game, world, id, name);
			world->dictionary[name] = id;

			auto player_bullet = static_cast<pPlayerBullet>(world->game_objects[id].get());
			player_bullet->LoadComponents(components_data);

			world->render_queue.emplace(player_bullet->layer, id);

			return player_bullet;
		}

		CPlayerBullet::CPlayerBullet(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CPlayerBullet(game, world, id, name) {
		}

		CPlayerBullet::~CPlayerBullet() {
		}

	}
}