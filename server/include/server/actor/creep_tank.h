#pragma once
#ifndef __SERVER__ACTOR__CREEP_TANK_H__
#define __SERVER__ACTOR__CREEP_TANK_H__

#include "engine/actor/creep_tank.h"
#include "engine/component/input_handler.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CCreepTank
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CCreepTank
			, public NSEngine::NSComponent::CInputHandler {
		public:
			static CCreepTank* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, nlohmann::json& data
			);

			CCreepTank(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CCreepTank();

			void HandleInput(uint32_t tick) override;

		};
		typedef CCreepTank* pCreepTank;

	}
}

#endif // !__SERVER__ACTOR__CREEP_TANK_H__
