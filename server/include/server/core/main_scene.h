#pragma once
#ifndef __SERVER__CORE__MAIN_SCENE_H__
#define __SERVER__CORE__MAIN_SCENE_H__

#include "server/core/scene.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSCore {

		class CMainScene
			: public NSServer::NSCore::CScene {
		protected:
			enum EState {
				Loading,
				Run
			};
			EState state = Loading;

			sf::View camera;
			sf::Font font;
			sf::Text text;

			uint32_t ready_client_count = 0;
			uint32_t load_client_count = 0;

		public:
			pWorld world = nullptr;

			std::map<uint32_t, uint32_t> player_ping;

			CMainScene(NSEngine::NSCore::pGame game);
			~CMainScene();

			void Load(std::string data_path) override;
			void Unload() override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			sf::View& GetCamera();

			void OnConnect(uint32_t connection_id) override;
			void OnDisconnect(uint32_t connection_id) override;
			bool ProcessPacket(std::shared_ptr<NSEngine::NSNetworks::CPacket> packet) override;

			void SendLoadPacket();
			void SendStartGamePacket();
			void SendReplyPingPacket(uint32_t client_id, uint32_t reply_ping_tick);

			void SendGameStatePacket();
		};
		typedef CMainScene* pMainScene;

	}
}

#endif // !__SERVER__MAIN_SCENE_H__
