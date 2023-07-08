#pragma once
#ifndef __SERVER__ACTOR__TANK_H__
#define __SERVER__ACTOR__TANK_H__

#include "server/core/game_object.h"
#include "engine/actor/power_up/tank.h"

namespace NSServer {
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
				, nlohmann::json& components_data
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

#endif // !__SERVER__ACTOR__TANK_H__
