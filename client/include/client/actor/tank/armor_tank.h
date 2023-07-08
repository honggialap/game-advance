#pragma once
#ifndef __CLIENT__ACTOR__ARMOR_TANK_H__
#define __CLIENT__ACTOR__ARMOR_TANK_H__

#include "client/core/game_object.h"
#include "engine/actor/tank/armor_tank.h"

#include "engine/component/render/remote.h"

namespace NSClient {
	namespace NSActor {

		class CArmorTank
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CArmorTank

			, public NSEngine::NSComponent::CRemote
		{
		public:
			static CArmorTank* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CArmorTank(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CArmorTank();

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;
		};
		typedef CArmorTank* pArmorTank;

	}
}

#endif // !__CLIENT__ACTOR__ARMOR_TANK_H__
