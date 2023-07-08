#pragma once
#ifndef __CLIENT__ACTOR__POWER_TANK_H__
#define __CLIENT__ACTOR__POWER_TANK_H__

#include "client/core/game_object.h"
#include "engine/actor/tank/power_tank.h"

#include "engine/component/render/remote.h"

namespace NSClient {
	namespace NSActor {

		class CPowerTank
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CPowerTank

			, public NSEngine::NSComponent::CRemote
		{
		public:
			static CPowerTank* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CPowerTank(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CPowerTank();

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;
		};
		typedef CPowerTank* pPowerTank;

	}
}

#endif // !__CLIENT__ACTOR__POWER_TANK_H__
