#include "game.h"
#include "lobby.h"
#include "world.h"

void Game::Initialize(std::string data_path) {
	std::ifstream data_file(data_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	auto& window_settings = data.at("window");
	std::string window_title = window_settings.at("title");
	unsigned int window_width = window_settings.at("width");
	unsigned int window_height = window_settings.at("height");
	float framerate = window_settings.at("framerate");

	window.create(
		sf::VideoMode(window_width, window_height),
		window_title,
		sf::Style::Titlebar | sf::Style::Close
	);
	window.setFramerateLimit(0);
	elapsed_ms_per_tick = 1000.0f / framerate;

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
	tick_per_ping = networks_settings.at("tick_per_ping");

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

		float temp_elapsed_ms = clock.GetMilliseconds();
		clock.Reset();

		elapsed_ms += temp_elapsed_ms;
		total_elapsed_ms += temp_elapsed_ms;

		ProcessNetworks();
		
		if (elapsed_ms >= elapsed_ms_per_tick) {
			if (IsApproved()) {
				if (tick_per_ping_count > 0) {
					tick_per_ping_count -= 1;
				}
				else {
					tick_per_ping_count = tick_per_ping;

					auto ping_packet = std::make_shared<Packet>(PacketType::Ping);
					*ping_packet << id << total_elapsed_ms;
					Send(ping_packet);
				}
			}

			tick_count += 1;
			scene->Update(elapsed_ms_per_tick);

			window.clear(sf::Color::Black);
			scene->Render(window);
			window.display();

			elapsed_ms -= elapsed_ms_per_tick;
		}
	}

	Shutdown();
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

	elapsed_ms = 0.0f;
	total_elapsed_ms = 0.0f;
	tick_count = 0;
	
	tick_per_ping_count = tick_per_ping;
	ping = 0;
}

pScene Game::CreateScene(unsigned int scene_type) {
	switch (scene_type) {

	case SCENE_TYPE_LOBBY: {
		return new Lobby(this);
		break;
	}

	case SCENE_TYPE_WORLD: {
		return new World(this);
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
		AssignId(id);
		printf("Get ID: %d\n", id);
		return true;
	}

	case PacketType::NotWelcome: {
		Disconnect();
		return true;
	}

	case PacketType::Ping: {
		float reply_total_elapsed_ms;
		*packet >> reply_total_elapsed_ms;
		ping = total_elapsed_ms - reply_total_elapsed_ms;
		//system("cls");
		//printf("PING: %f \n", ping);
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
