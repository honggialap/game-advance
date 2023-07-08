#pragma once
#ifndef __CLIENT__ACTOR__TANK_H__
#define __CLIENT__ACTOR__TANK_H__

#include "client/core/game_object.h"
#include "engine/actor/power_up/tank.h"

namespace NSClient {
	namespace NSActor {

		class CTank
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CTank
		{
		public:
			static CTank* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CTank(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CTank();

		};
		typedef CTank* pTank;

	}
}

#endif // !__CLIENT__ACTOR__TANK_H__
