#pragma once	
#ifndef __CLIENT__ACTOR__BASIC_TANK_H__
#define __CLIENT__ACTOR__BASIC_TANK_H__

#include "client/core/game_object.h"
#include "engine/actor/tank/basic_tank.h"

#include "engine/component/render/remote.h"

namespace NSClient {
	namespace NSActor {

		class CBasicTank
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CBasicTank

			, public NSEngine::NSComponent::CRemote
		{
		public:
			static CBasicTank* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CBasicTank(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CBasicTank();

		};
		typedef CBasicTank* pBasicTank;

	}
}

#endif // !__CLIENT__ACTOR__BASIC_TANK_H__
