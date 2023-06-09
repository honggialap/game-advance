#include "server/core/game.h"

#include "server/core/lobby_scene.h"
#include "server/core/main_scene.h"

namespace NSServer {
	namespace NSCore {

		void CGame::Initialize(std::string data_path) {
			NSEngine::NSCore::CGame::Initialize(data_path);

			std::ifstream data_file(data_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

			auto& networks_settings = data.at("networks");
			std::string address = networks_settings.at("address");
			uint32_t port = networks_settings.at("port");
			uint32_t max_connection = networks_settings.at("max_connection");

			NSEngine::NSNetworks::CIPEndPoint host_address = NSEngine::NSNetworks::CIPEndPoint(address.c_str(), port);
			SetHostAddress(host_address);

			uint32_t open_slots = networks_settings.at("max_connection");
			SetMaxConnectionLimit(open_slots);

			CServer::Initialize();
			CServer::StartListen();
		}

		void CGame::Shutdown() {
			NSEngine::NSCore::CGame::Shutdown();
			CServer::StopListen();
			CServer::Shutdown();
		}

		void CGame::Run(std::string data_path) {
			Initialize(data_path);

			std::thread networks_processing_thread(
				[&]() {
					while (window.isOpen()) {
						ProcessNetworks();
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
					ProcessPackets();
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

			networks_processing_thread.join();
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

		void CGame::OnConnect(uint32_t connection_id) {
			if (connections.size() > max_connection_count) {
				auto not_welcome_packet = std::make_shared<NSEngine::NSNetworks::CPacket>(NSEngine::EPacketType::NOT_WELCOME);
				Send(connection_id, not_welcome_packet);
			}
			else {
				auto welcome_packet = std::make_shared<NSEngine::NSNetworks::CPacket>(NSEngine::EPacketType::WELCOME);
				*welcome_packet << connection_id;
				Send(connection_id, welcome_packet);
			}

			if (scene.get() && dynamic_cast<NSServer::NSCore::pScene>(scene.get())) {
				dynamic_cast<NSServer::NSCore::pScene>(scene.get())->OnConnect(connection_id);
			}
		}

		void CGame::OnDisconnect(uint32_t connection_id) {
			if (scene && dynamic_cast<NSServer::NSCore::pScene>(scene.get())) {
				dynamic_cast<NSServer::NSCore::pScene>(scene.get())->OnDisconnect(connection_id);
			}
		}

		bool CGame::ProcessPacket(std::shared_ptr<NSEngine::NSNetworks::CPacket> packet) {
			switch (packet->GetPacketType()) {

			default: {
				if (scene && dynamic_cast<NSServer::NSCore::pScene>(scene.get())) {
					return dynamic_cast<NSServer::NSCore::pScene>(scene.get())->ProcessPacket(packet);
				}
				return false;
			}

			}
		}

	}
}