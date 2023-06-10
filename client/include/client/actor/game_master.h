#pragma once
#ifndef __CLIENT__ACTOR__GAME_MASTER_H__
#define __CLIENT__ACTOR__GAME_MASTER_H__

#include "engine/actor/game_master.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CGameMaster
			: public NSEngine::NSActor::CGameMaster
			, public NSClient::NSCore::CGameObject {
		public:
			static CGameMaster* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world,
				std::string name,
				std::string data_path
				);

			CGameMaster(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CGameMaster();

			void Load(std::string data_path) override;
			void Unload() override;

			void Update(float elapsed) override;
		};
		typedef CGameMaster* pGameMaster;

	}
}

#endif // !__CLIENT__ACTOR__GAME_MASTER_H__
