#pragma once
#ifndef __CLIENT__CORE__MAIN_SCENE_H__
#define __CLIENT__CORE__MAIN_SCENE_H__

#include "client/core/scene.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSCore {
		
		class CMainScene
			: public NSClient::NSCore::CScene {
		protected:
			enum EState {
				Loading,
				Run
			};
			EState state = Loading;

			sf::View camera;
			sf::Font font;
			sf::Text text;

			pWorld world = nullptr;

			bool ready_sent = false;
			bool ping_sent = false;
			uint32_t ping_tick = 0;

		public:
			CMainScene(NSEngine::NSCore::pGame game);
			~CMainScene();

			void Load(std::string data_path) final;
			void Unload() final;

			void Update(float elapsed) final;
			void Render(sf::RenderWindow& window) final;

			sf::View& GetCamera();

			void OnConnect() final;
			void OnDisconnect() final;
			void OnConnectFail() final;
			bool ProcessPacket(std::shared_ptr<NSEngine::NSNetworks::CPacket> packet) override;

			void SendReadyPacket();
			void SendLoadPacket();
			void SendPingPacket();
		};

	}
}

#endif // !__CLIENT__CORE__MAIN_SCENE_H__
