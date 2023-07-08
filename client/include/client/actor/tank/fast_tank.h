#pragma once
#ifndef __CLIENT__ACTOR__FAST_TANK_H__
#define __CLIENT__ACTOR__FAST_TANK_H__

#include "client/core/game_object.h"
#include "engine/actor/tank/fast_tank.h"

#include "engine/component/render/remote.h"

namespace NSClient {
	namespace NSActor {

		class CFastTank
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CFastTank

			, public NSEngine::NSComponent::CRemote
		{
		public:
			static CFastTank* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CFastTank(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CFastTank();

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;
		};
		typedef CFastTank* pFastTank;

	}
}

#endif // !__CLIENT__ACTOR__FAST_TANK_H__
