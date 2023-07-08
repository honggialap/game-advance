#include "server/actor/headquarter.h"
#include "server/core/game.h"
#include "server/core/world.h"

#include "server/actor/game_master.h"
#include "server/actor/tank/bullet.h"

namespace NSServer {
	namespace NSActor {

		pHeadquarter CHeadquarter::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, nlohmann::json& components_data
		) {
			if (world->dictionary.find("name") != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CHeadquarter>(game, world, id, name);
			world->dictionary[name] = id;

			auto game_object = static_cast<pHeadquarter>(world->game_objects[id].get());
			game_object->LoadComponents(components_data);

			world->render_queue.emplace(game_object->layer, id);

			return game_object;
		}

		CHeadquarter::CHeadquarter(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world) 
			, NSEngine::NSActor::CHeadquarter(game, world, id, name) {
		}

		CHeadquarter::~CHeadquarter() {
		}

		void CHeadquarter::Update(float elapsed) {
			if (is_shovel_activated) {
				shovel_timer -= elapsed;
				if (shovel_timer < 0.0f)
					DeactivateShovel();
			}
		}

		void CHeadquarter::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
			if (dynamic_cast<NSEngine::NSActor::pBullet>(other)) {
				is_alive = false;
				//game_master->GameLost();
			}
		}

		void CHeadquarter::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
		}

	}
}