#pragma once
#ifndef __SERVER__ACTOR__BASIC_TANK_H__
#define __SERVER__ACTOR__BASIC_TANK_H__

#include "server/core/game_object.h"
#include "engine/actor/tank/basic_tank.h"

#include "engine/component/system/input_handler.h"

namespace NSServer {
	namespace NSActor {

		class CBasicTank
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CBasicTank

			, public NSEngine::NSComponent::CInputHandler
		{
		public:
			static CBasicTank* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, nlohmann::json& components_data
			);

			CBasicTank(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CBasicTank();

			void HandleInput(uint32_t tick) override;

		};
		typedef CBasicTank* pBasicTank;

	}
}

#endif // !__SERVER__ACTOR__BASIC_TANK_H__
