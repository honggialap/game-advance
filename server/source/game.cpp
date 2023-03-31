#include "game.h"
#include "lobby.h"
#include "world.h"

void Game::Initialize(std::string data_path) {
	std::ifstream data_file(data_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	unsigned int window_width = data.at("width");
	unsigned int window_height = data.at("height");
	std::string window_title = data.at("title");
	window.create(
		sf::VideoMode(window_width, window_height),
		window_title,
		sf::Style::Titlebar | sf::Style::Close
	);
	window.setFramerateLimit(0);

	for (auto& scene : data.at("scene_list")) {
		unsigned int id = scene.at("id");
		unsigned int type = scene.at("type");
		std::string data_path = scene.at("data_path");
		scene_list[id] = std::make_pair(type, data_path);
	}
	PlayScene(data.at("start_scene_id"));

	float framerate = data.at("framerate");
	tick_per_frame = 1000.0f / framerate;

	Server::Initialize();
	Server::StartListening(IPEndPoint("::1", 27015), 3);
}

void Game::Shutdown() {
	if (scene) scene->Unload();

	Server::StopListening();
	Server::Shutdown();
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

		Listening();
		ProcessNetworks();

		elapsed_ms += clock.GetMilliseconds();
		clock.Reset();

		if (elapsed_ms >= tick_per_frame) {
			ProcessIncomming();
			scene->Update(elapsed_ms);

			window.clear(sf::Color::Black);
			scene->Render(window);
			window.display();

			elapsed_ms = 0.0f;
		}
		else {
			Sleep((DWORD)tick_per_frame - elapsed_ms);
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

void Game::OnConnect(uint32_t connection_id) {
	scene->OnConnect(connection_id);
}

void Game::OnDisconnect(uint32_t connection_id) {
	scene->OnDisconnect(connection_id);
}

bool Game::ProcessPacket(std::shared_ptr<Packet> packet) {
	return scene->ProcessPacket(packet);
}
