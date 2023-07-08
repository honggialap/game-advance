#pragma once
#ifndef __SERVER__CORE__LOBBY_SCENE_H__
#define __SERVER__CORE__LOBBY_SCENE_H__

#include "server/core/scene.h"

namespace NSServer {
	namespace NSCore {

		class CLobbyScene
			: public NSServer::NSCore::CScene {
		protected:
			enum EState {
				Picking,
				Locked
			};
			EState state = EState::Picking;

			sf::Texture texture;
			sf::Sprite sprite;
			sf::Font font;
			sf::Text text;

			float count_down = 0;

		public:
			CLobbyScene(NSEngine::NSCore::pGame game);
			~CLobbyScene();

			void Load(std::string data_path) override;
			void Unload() override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnConnect(uint32_t connection_id) override;
			void OnDisconnect(uint32_t connection_id) override;
			bool ProcessPacket(std::shared_ptr<NSEngine::NSNetworks::CPacket> packet) override;

			void SendConfirmPacket();
			void SendNextScenePacket(uint32_t scene_id);

			void SetPlayerPick(uint32_t player_id, uint32_t client_id);
			void SetPlayerLock(uint32_t client_id);
		};
		typedef CLobbyScene* pLobbyScene;

	}
}

#endif // !__SERVER__CORE__LOBBY_SCENE_H__
