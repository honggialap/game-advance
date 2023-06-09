#include "client/core/game.h"

#include "client/core/lobby_scene.h"
#include "client/core/main_scene.h"

namespace NSClient {
	namespace NSCore {

		void CGame::Initialize(std::string data_path) {
			NSEngine::NSCore::CGame::Initialize(data_path);

			std::ifstream data_file(data_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

			auto& networks_settings = data.at("networks");
			std::string address = networks_settings.at("address");
			uint32_t port = networks_settings.at("port");

			NSEngine::NSNetworks::CIPEndPoint host_address = NSEngine::NSNetworks::CIPEndPoint(address.c_str(), port);
			CClient::Initialize();
			CClient::SetHostAddress(host_address);
		}

		void CGame::Shutdown() {
			NSEngine::NSCore::CGame::Shutdown();
			CClient::Shutdown();
		}

		void CGame::Run(std::string data_path) {
			Initialize(data_path);

			std::thread network_processing_thread(
				[&]() {
					while (window.isOpen()) {
						if (is_connecting) {
							ProcessNetworks();
						}
					}
				}
			);

			while (window.isOpen()) {
				sf::Event window_event;
				while (window.pollEvent(window_event)) {
					switch (window_event.type) {
					case sf::Event::Closed: {
						Exit();
						break;
					}

					default:
						break;
					}
				}

				if (load_scene) LoadScene();

				float elapsed_ms = clock.GetMilliseconds();
				clock.Reset();

				update_elapsed_ms += elapsed_ms;
				while (update_elapsed_ms >= elapsed_ms_per_update) {
					if (is_connecting) {
						ProcessPackets();
					}
					scene->Update(elapsed_ms_per_update);
					update_elapsed_ms -= elapsed_ms_per_update;
				}

				render_elapsed_ms += elapsed_ms;
				while (render_elapsed_ms >= elapsed_ms_per_render) {
					window.clear(sf::Color::Black);
					scene->Render(window);
					window.display();
					render_elapsed_ms -= elapsed_ms_per_render;
				}
			}

			network_processing_thread.join();
			Shutdown();
		}

		NSEngine::NSCore::pScene CGame::CreateScene(NSEngine::ESceneType scene_type) {
			switch (scene_type) {

			case NSEngine::ESceneType::LOBBY_SCENE: {
				return new CLobbyScene(this);
				break;
			}

			case NSEngine::ESceneType::MAIN_SCENE: {
				return new CMainScene(this);
				break;
			}

			default: {
				return nullptr;
				break;
			}

			}
		}

		void CGame::OnConnect() {
			if (scene.get() && dynamic_cast<NSClient::NSCore::pScene>(scene.get())) {
				dynamic_cast<NSClient::NSCore::pScene>(scene.get())->OnConnect();
			}
		}

		void CGame::OnDisconnect() {
			if (scene.get() && dynamic_cast<NSClient::NSCore::pScene>(scene.get())) {
				dynamic_cast<NSClient::NSCore::pScene>(scene.get())->OnDisconnect();
			}
		}

		void CGame::OnConnectFail() {
			if (scene.get() && dynamic_cast<NSClient::NSCore::pScene>(scene.get())) {
				dynamic_cast<NSClient::NSCore::pScene>(scene.get())->OnConnectFail();
			}
		}

		bool CGame::ProcessPacket(std::shared_ptr<NSEngine::NSNetworks::CPacket> packet) {
			switch (packet->GetPacketType()) {

			case NSEngine::EPacketType::WELCOME: {
				uint32_t id;
				*packet >> id;

				AssignClientId(id);
				printf("Get ID: %d\n", id);

				is_accepted = true;

				return true;
			}

			case NSEngine::EPacketType::NOT_WELCOME: {
				Disconnect();
				return true;
			}

			default: {
				if (scene.get() && dynamic_cast<NSClient::NSCore::pScene>(scene.get())) {
					return dynamic_cast<NSClient::NSCore::pScene>(scene.get())->ProcessPacket(packet);
				}
				return false;
			}

			}
		}

	}
}
