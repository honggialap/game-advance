#pragma once
#ifndef __CLIENT__ACTOR__GAME_MASTER_H__
#define __CLIENT__ACTOR__GAME_MASTER_H__

#include "engine/actor/game_master.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CGameMaster
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CGameMaster {
		public:
			static CGameMaster* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				);

			CGameMaster(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CGameMaster();

		};
		typedef CGameMaster* pGameMaster;

	}
}

#endif // !__CLIENT__ACTOR__GAME_MASTER_H__
