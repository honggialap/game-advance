#pragma once
#ifndef __SERVER__CORE__GAME_H__
#define __SERVER__CORE__GAME_H__

#include "engine/common.h"
#include "engine/core/game.h"
#include "server/networks/server.h"

namespace NSServer {
	namespace NSCore {

		class CGame
			: public NSEngine::NSCore::CGame
			, public NSServer::NSNetworks::CServer {
		public:
			std::map<uint32_t, std::pair<uint32_t, bool>> players;

			void Initialize(std::string data_path) final;
			void Shutdown() final;

			void Run(std::string data_path) final;

			NSEngine::NSCore::pScene CreateScene(NSEngine::ESceneType scene_type) final;

			bool ProcessPacket(std::shared_ptr<NSEngine::NSNetworks::CPacket> packet) final;

			void OnConnect(uint32_t connection_id) final;
			void OnDisconnect(uint32_t connection_id) final;
		};
		typedef CGame* pGame;

	}
}

#endif // !__SERVER__CORE__GAME_SERVER_H__
