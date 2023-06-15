#pragma once
#ifndef __CLIENT__ACTOR__POWER_UP_H__
#define __CLIENT__ACTOR__POWER_UP_H__

#include "engine/actor/power_up.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CPowerUp
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CPowerUp {
		public:
			static CPowerUp* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CPowerUp(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CPowerUp();

		};
		typedef CPowerUp* pPowerUp;

	}
}

#endif // !__CLIENT__ACTOR__POWER_UP_H__
