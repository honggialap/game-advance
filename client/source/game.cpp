#include "game.h"
#include "lobby_scene.h"
#include "main_scene.h"

void Game::Initialize(std::string data_path) {
	std::ifstream data_file(data_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	auto& window_settings = data.at("window");
	std::string window_title = window_settings.at("title");
	unsigned int window_width = window_settings.at("width");
	unsigned int window_height = window_settings.at("height");
	float update_rate = window_settings.at("update_rate");
	float render_rate = window_settings.at("render_rate");

	window.create(
		sf::VideoMode(window_width, window_height),
		window_title,
		sf::Style::Titlebar | sf::Style::Close
	);
	window.setFramerateLimit(0);
	elapsed_ms_per_update = 1000.0f / update_rate;
	elapsed_ms_per_render = 1000.0f / render_rate;

	auto& scenes = data.at("scenes");
	for (auto& scene : scenes.at("scene_list")) {
		unsigned int id = scene.at("id");
		unsigned int type = scene.at("type");
		std::string data_path = scene.at("data_path");
		scene_list[id] = std::make_pair(type, data_path);
	}
	PlayScene(scenes.at("start_scene_id"));

	auto& networks_settings = data.at("networks");
	std::string address = networks_settings.at("address");
	uint32_t port = networks_settings.at("port");

	IPEndPoint host_address = IPEndPoint(address.c_str(), port);
	Client::Initialize(host_address);
	Client::Connect();
}

void Game::Shutdown() {
	if (scene) scene->Unload();

	Client::Disconnect();
	Client::Shutdown();
}

void Game::Run(std::string data_path) {
	Initialize(data_path);

	auto network_process = [this]() {
		while (ProcessNetworks()) {
		}
	};
	std::thread networks_thread(network_process);

	while (window.isOpen()) {
		sf::Event window_event;
		while (window.pollEvent(window_event)) {
			switch (window_event.type) {
			case sf::Event::Closed: {
				window.close();
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
		if (update_elapsed_ms >= elapsed_ms_per_update) {
			ProcessPackets();
			scene->Update(elapsed_ms_per_update);
			update_elapsed_ms -= elapsed_ms_per_update;
		}

		render_elapsed_ms += elapsed_ms;
		if (render_elapsed_ms >= elapsed_ms_per_render) {
			window.clear(sf::Color::Black);
			scene->Render(window);
			window.display();
			render_elapsed_ms -= elapsed_ms_per_render;
		}

	}

	Shutdown();
	networks_thread.join();
}

void Game::PlayScene(unsigned int scene_id) {
	if (scene_list.find(scene_id) == scene_list.end()) {
		printf("Scene [%d] not found!\n", scene_id);
		return;
	}

	if (scene_id == next_scene_id) {
		printf("Scene [%d] is already playing or queuing for load!\n", scene_id);
		return;
	}

	load_scene = true;
	next_scene_id = scene_id;
}

void Game::LoadScene() {
	load_scene = false;

	if (scene) scene->Unload();

	auto next_scene = scene_list.find(next_scene_id)->second;
	scene.reset(CreateScene(next_scene.first));

	scene->Load(next_scene.second);

	update_elapsed_ms = 0.0f;
	render_elapsed_ms = 0.0f;
}

pScene Game::CreateScene(unsigned int scene_type) {
	switch (scene_type) {

	case SCENE_TYPE_LOBBY: {
		return new LobbyScene(this);
		break;
	}

	case SCENE_TYPE_MAIN: {
		return new MainScene(this);
		break;
	}

	default: {
		return nullptr;
		break;
	}

	}
}

void Game::OnConnect() {
	if (scene) {
		scene->OnConnect();
	}
}

void Game::OnDisconnect() {
	if (scene) {
		scene->OnDisconnect();
	}
}

void Game::OnConnectFail() {
	if (scene) {
		scene->OnConnectFail();
	}
}

bool Game::ProcessPacket(std::shared_ptr<Packet> packet) {
	switch (packet->GetPacketType()) {
	case PacketType::Welcome: {
		uint32_t id;
		*packet >> id;
		AssignClientId(id);
		printf("Get ID: %d\n", id);
		return true;
	}

	case PacketType::NotWelcome: {
		Disconnect();
		return true;
	}

	default: {
		if (scene) {
			return scene->ProcessPacket(packet);
		}
		return false;
	}

	}
}
