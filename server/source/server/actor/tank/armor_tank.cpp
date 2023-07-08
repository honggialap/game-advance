#include "server/actor/tank/armor_tank.h"
#include "server/core/game.h"
#include "server/core/world.h"

#include "server/actor/terrain/brick.h"

namespace NSServer {
	namespace NSActor {

		pArmorTank CArmorTank::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, nlohmann::json& components_data
		) {
			if (world->dictionary.find(name) != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CArmorTank>(game, world, id, name);
			world->dictionary[name] = id;

			auto game_object = static_cast<pArmorTank>(world->game_objects[id].get());
			game_object->LoadComponents(components_data);

			world->render_queue.emplace(game_object->layer, id);

			return game_object;
		}

		CArmorTank::CArmorTank(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CArmorTank(game, world, id, name) {
		}

		CArmorTank::~CArmorTank() {
		}

		void CArmorTank::HandleInput(uint32_t tick) {
		}

	}
}
