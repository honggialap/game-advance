#include "game_client.h"
#include "lobby_scene.h"
#include "main_scene.h"

void GameClient::Initialize(std::string data_path) {
	Game::Initialize(data_path);

	std::ifstream data_file(data_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	auto& networks_settings = data.at("networks");
	std::string address = networks_settings.at("address");
	uint32_t port = networks_settings.at("port");

	IPEndPoint host_address = IPEndPoint(address.c_str(), port);
	Client::Initialize();
	Client::SetHostAddress(host_address);
}

void GameClient::Shutdown() {
	Game::Shutdown();
	Client::Shutdown();
}

void GameClient::Run(std::string data_path) {
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

pScene GameClient::CreateScene(uint32_t scene_type) {
	switch (scene_type) {

	case SCENE_LOBBY: {
		client_scene = new LobbyScene(this);
		return client_scene;
		break;
	}

	case SCENE_MAIN: {
		client_scene = new MainScene(this);
		return client_scene;
		break;
	}

	default: {
		client_scene = nullptr;
		return nullptr;
		break;
	}

	}
}

void GameClient::OnConnect() {
	if (client_scene) {
		client_scene->OnConnect();
	}
}

void GameClient::OnDisconnect() {
	if (client_scene) {
		client_scene->OnDisconnect();
	}
}

void GameClient::OnConnectFail() {
	if (client_scene) {
		client_scene->OnConnectFail();
	}
}

bool GameClient::ProcessPacket(std::shared_ptr<Packet> packet) {
	if (!Client::ProcessPacket(packet)) {
		if (client_scene) {
			return client_scene->ProcessPacket(packet);
		}
		return false;
	}
	else {
		return true;
	}
}
