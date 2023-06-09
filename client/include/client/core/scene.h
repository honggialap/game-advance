#pragma once
#ifndef __CLIENT__CORE__SCENE_H__
#define __CLIENT__CORE__SCENE_H__

#include "engine/networks/packet.h"
#include "engine/core/scene.h"

namespace NSClient {
	namespace NSCore {

		class CGame;
		typedef CGame* pGame;

		class CScene 
			: public NSEngine::NSCore::CScene {
		protected:
			pGame game_client = nullptr;

		public:
			CScene(NSEngine::NSCore::pGame game);
			virtual ~CScene() = 0;

			virtual void OnConnect() = 0;
			virtual void OnDisconnect() = 0;
			virtual void OnConnectFail() = 0;
			virtual bool ProcessPacket(std::shared_ptr<NSEngine::NSNetworks::CPacket> packet) = 0;
		};
		typedef CScene* pScene;

	}
}

#endif // !__CLIENT__CORE__SCENE_H__
