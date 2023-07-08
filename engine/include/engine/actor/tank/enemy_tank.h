#pragma once
#ifndef __ENGINE__ACTOR__ENEMY_TANK_H__
#define __ENGINE__ACTOR__ENEMY_TANK_H__

#include "engine/actor/tank/base_tank.h"
#include "engine/component/control/ai_control.h"
#include "engine/component/stat/reward.h"

#include "engine/actor/effect/score.h"

namespace NSEngine {
	namespace NSActor {

		class CEnemyTank
			: public NSActor::CBaseTank
			, public NSComponent::CAIControl
			, public NSComponent::CReward
		{
		protected:
			pScore score_effect = nullptr;

		public:
			CEnemyTank(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CEnemyTank();

			void AddGameMaster(std::string name) override;

			void AddScoreEffect(std::string name);
		};
		typedef CEnemyTank* pEnemyTank;

	}
}

#endif // !__ENGINE__ACTOR__ENEMY_TANK_H__
