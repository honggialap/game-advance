#pragma once
#ifndef __SERVER__ACTOR__TURRET_H__
#define __SERVER__ACTOR__TURRET_H__

#include "engine/actor/turret.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CTurret
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CTurret {
		public:
			static CTurret* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, nlohmann::json & data
			);

			CTurret(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CTurret();

		};
		typedef CTurret* pTurret;

	}
}

#endif // !__SERVER__ACTOR__TURRET_H__
