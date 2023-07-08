#pragma once
#ifndef __SERVER__ACTOR__GAME_MASTER_H__
#define __SERVER__ACTOR__GAME_MASTER_H__

#include "server/core/game_object.h"
#include "engine/actor/game_master.h"

namespace NSServer {
	namespace NSActor {

		class CGameMaster
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CGameMaster 
		{
		public:
			static CGameMaster* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, nlohmann::json& components_data
			);

			CGameMaster(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CGameMaster();

			void Update(float elapsed) override;

			void PackLoadPacket(NSEngine::NSNetworks::CPacket* packet) final;
		};
		typedef CGameMaster* pGameMaster;

	}
}

#endif // !__SERVER__ACTOR__GAME_MASTER_H__
