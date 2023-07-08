#pragma once
#ifndef __SERVER__ACTOR__FAST_TANK_H__
#define __SERVER__ACTOR__FAST_TANK_H__

#include "server/core/game_object.h"
#include "engine/actor/tank/fast_tank.h"

#include "engine/component/system/input_handler.h"

namespace NSServer {
	namespace NSActor {

		class CFastTank
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CFastTank

			, public NSEngine::NSComponent::CInputHandler
		{
		public:
			static CFastTank* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, nlohmann::json& components_data
			);

			CFastTank(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CFastTank();

			void HandleInput(uint32_t tick) override;

		};
		typedef CFastTank* pFastTank;

	}
}

#endif // !__SERVER__ACTOR__FAST_TANK_H__
