#include "engine/actor/tank/enemy_tank.h"
#include "engine/core/game.h"
#include "engine/core/world.h"

#include "engine/actor/game_master.h"

namespace NSEngine {
	namespace NSActor {

		CEnemyTank::CEnemyTank(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSActor::CBaseTank(game, world, id, name)
		{
			type = EActorType::INVALID_ACTOR;
		}

		CEnemyTank::~CEnemyTank() {
		}

		void CEnemyTank::AddGameMaster(std::string name) {
			uint32_t id = world->dictionary[name];
			NSCore::pGameObject game_object = world->game_objects[id].get();

			game_master = dynamic_cast<pGameMaster>(game_object);
			game_master->AddEnemyTank(GetName());
		}

		void CEnemyTank::AddScoreEffect(std::string name) {
			uint32_t id = world->dictionary[name];
			NSCore::pGameObject game_object = world->game_objects[id].get();

			score_effect = dynamic_cast<pScore>(game_object);
		}

	}
}