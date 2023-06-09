#pragma once
#ifndef __SERVER__ACTOR__GAME_MASTER_H__
#define __SERVER__ACTOR__GAME_MASTER_H__

#include "engine/actor/game_master.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CGameMaster
			: public NSEngine::NSActor::CGameMaster
			, public NSServer::NSCore::CGameObject {
		public:
			static CGameMaster* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, std::string data_path
			);

			CGameMaster(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
			);
			~CGameMaster();

			void Load(std::string data_path) override;
			void Unload() override;

			void Update(float elapsed) override;
		};
		typedef CGameMaster* pGameMaster;

	}
}

#endif // !__SERVER__ACTOR__GAME_MASTER_H__
