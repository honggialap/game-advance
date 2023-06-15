#pragma once	
#ifndef __CLIENT__ACTOR__CREEP_TANK_H__
#define __CLIENT__ACTOR__CREEP_TANK_H__

#include "engine/actor/creep_tank.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CCreepTank
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CCreepTank {
		public:
			static CCreepTank* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CCreepTank(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CCreepTank();

		};
		typedef CCreepTank* pCreepTank;

	}
}

#endif // !__CLIENT__ACTOR__CREEP_TANK_H__
