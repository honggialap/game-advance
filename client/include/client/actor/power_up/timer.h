#pragma once
#ifndef __CLIENT__ACTOR__TIMER_H__
#define __CLIENT__ACTOR__TIMER_H__

#include "client/core/game_object.h"
#include "engine/actor/power_up/timer.h"

namespace NSClient {
	namespace NSActor {

		class CTimer
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CTimer
		{
		public:
			static CTimer* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CTimer(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CTimer();

		};
		typedef CTimer* pTimer;

	}
}

#endif // !__CLIENT__ACTOR__TIMER_H__
