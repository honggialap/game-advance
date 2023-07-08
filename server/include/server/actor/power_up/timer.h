#pragma once
#ifndef __SERVER__ACTOR__TIMER_H__
#define __SERVER__ACTOR__TIMER_H__

#include "server/core/game_object.h"
#include "engine/actor/power_up/timer.h"

namespace NSServer {
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
				, nlohmann::json& components_data
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

#endif // !__SERVER__ACTOR__TIMER_H__
