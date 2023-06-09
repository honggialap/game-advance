#pragma once
#ifndef __SERVER__CORE__SCENE_H__
#define __SERVER__CORE__SCENE_H__

#include "engine/networks/packet.h"
#include "engine/core/scene.h"

namespace NSServer {
	namespace NSCore {

		class CGame;
		typedef CGame* pGame;

		class CScene 
			: public NSEngine::NSCore::CScene {
		protected:
			pGame game_server = nullptr;

		public:
			CScene(NSEngine::NSCore::pGame game);
			virtual ~CScene() = 0;

			virtual void OnConnect(uint32_t connection_id) = 0;
			virtual void OnDisconnect(uint32_t connection_id) = 0;
			virtual bool ProcessPacket(std::shared_ptr<NSEngine::NSNetworks::CPacket> packet) = 0;
		};
		typedef CScene* pScene;

	}
}

#endif // !__SERVER__SCENE_H__
