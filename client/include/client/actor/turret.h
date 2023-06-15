#pragma once
#ifndef __CLIENT__ACTOR__TURRET_H__
#define __CLIENT__ACTOR__TURRET_H__

#include "engine/actor/turret.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CTurret
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CTurret {
		public:
			static CTurret* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
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

#endif // !__CLIENT__ACTOR__TURRET_H__
