#pragma once
#ifndef __CLIENT__CORE__LOBBY_SCENE_H__
#define __CLIENT__CORE__LOBBY_SCENE_H__

#include "client/core/scene.h"

namespace NSClient {
	namespace NSCore {

		class CLobbyScene
			: public NSClient::NSCore::CScene {
		protected:
			enum EState {
				Connecting,
				Picking,
				Locked
			};
			EState state = EState::Connecting;

			sf::Texture texture;
			sf::Sprite sprite;
			sf::Font font;
			sf::Text text;

			bool pick_sent = false;
			bool lockable = false;

		public:
			CLobbyScene(NSEngine::NSCore::pGame game);
			~CLobbyScene();

			void Load(std::string data_path) override;
			void Unload() override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnConnect() override;
			void OnDisconnect() override;
			void OnConnectFail() override;
			bool ProcessPacket(std::shared_ptr<NSEngine::NSNetworks::CPacket> packet) override;

			void SendPickPacket(uint32_t player_id_value);
			void SendLockPacket();
		};

	}
}

#endif // !__CLIENT__CORE__LOBBY_SCENE_H__
