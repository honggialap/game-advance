#pragma once
#ifndef __SERVER__ACTOR__POWER_TANK_H__
#define __SERVER__ACTOR__POWER_TANK_H__

#include "server/core/game_object.h"
#include "engine/actor/tank/power_tank.h"

#include "engine/component/system/input_handler.h"

namespace NSServer {
	namespace NSActor {

		class CPowerTank
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CPowerTank

			, public NSEngine::NSComponent::CInputHandler
		{
		public:
			static CPowerTank* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, nlohmann::json& components_data
			);

			CPowerTank(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CPowerTank();

			void HandleInput(uint32_t tick) override;

		};
		typedef CPowerTank* pPowerTank;

	}
}

#endif // !__SERVER__ACTOR__POWER_TANK_H__
