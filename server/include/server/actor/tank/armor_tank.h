#pragma once
#ifndef __SERVER__ACTOR__ARMOR_TANK_H__
#define __SERVER__ACTOR__ARMOR_TANK_H__

#include "server/core/game_object.h"
#include "engine/actor/tank/armor_tank.h"

#include "engine/component/system/input_handler.h"

namespace NSServer {
	namespace NSActor {

		class CArmorTank
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CArmorTank

			, public NSEngine::NSComponent::CInputHandler
		{
		public:
			static CArmorTank* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, nlohmann::json& components_data
			);

			CArmorTank(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CArmorTank();

			void HandleInput(uint32_t tick) override;

		};
		typedef CArmorTank* pArmorTank;

	}
}

#endif // !__SERVER__ACTOR__ARMOR_TANK_H__
