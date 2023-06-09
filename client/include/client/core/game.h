#pragma once
#ifndef __CLIENT__CORE__GAME_H__
#define __CLIENT__CORE__GAME_H__

#include "engine/common.h"
#include "engine/core/game.h"
#include "client/networks/client.h"

namespace NSClient {
	namespace NSCore {

		class CGame
			: public NSEngine::NSCore::CGame
			, public NSClient::NSNetworks::CClient {
		protected:
			uint32_t player_id = 0;

		public:
			void SetPlayerId(uint32_t value) { player_id = value; }
			uint32_t GetPlayerId() { return player_id; }

			void Initialize(std::string data_path) final;
			void Shutdown() final;

			void Run(std::string data_path) final;

			NSEngine::NSCore::pScene CreateScene(NSEngine::ESceneType scene_type) final;

			void OnConnect() final;
			void OnDisconnect() final;
			void OnConnectFail() final;
			bool ProcessPacket(std::shared_ptr<NSEngine::NSNetworks::CPacket> packet) final;
		};
		typedef CGame* pGame;

	}
}

#endif // !__CLIENT__CORE__GAME_H__
