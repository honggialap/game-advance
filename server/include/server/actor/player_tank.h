#pragma once
#ifndef __SERVER__ACTOR__PLAYER_TANK_H__
#define __SERVER__ACTOR__PLAYER_TANK_H__

#include "engine/actor/player_tank.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CPlayerTank
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CPlayerTank {
		public:
			static CPlayerTank* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, nlohmann::json& components_data
			);

			CPlayerTank(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CPlayerTank();

		};
		typedef CPlayerTank* pPlayerTank;

	}
}

#endif // !__SERVER__ACTOR__PLAYER_TANK_H__
