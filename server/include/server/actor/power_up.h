#pragma once
#ifndef __SERVER__ACTOR__POWER_UP_H__
#define __SERVER__ACTOR__POWER_UP_H__

#include "engine/actor/power_up.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CPowerUp
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CPowerUp {
		public:
			static CPowerUp* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, nlohmann::json& components_data
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

#endif // !__SERVER__ACTOR__POWER_UP_H__
