#include "lobby.h"
#include "game.h"

Lobby::Lobby(pGame game) : Scene(game) {
}

Lobby::~Lobby() {
}

void Lobby::Load(std::string data_path) {
	std::ifstream data_file(data_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	font.loadFromFile("data/resources/fonts/arial.ttf");
	text.setFont(font);

	for (int i = 1; i <= 4; i++) {
		game->players[i] = std::make_pair(uint32_t(0), false);
	}
}

void Lobby::Unload() {
}

void Lobby::Update(float elapsed) {
	std::stringstream displaying;
	displaying << "PLAYER \n";
	for (auto& player : game->players) {
		std::string status = player.second.second ? "LOCKED" : "PICKING";
		displaying << player.first << " : " << player.second.first << " : " << status << "\n";
	}
	text.setString(displaying.str());

	auto player_confirm_packet = std::make_shared<Packet>(PacketType::PlayerConfirm);
	*player_confirm_packet << uint32_t(4);
	for (auto& player : game->players) {
		*player_confirm_packet << player.first << player.second.first << player.second.second;
	}
	game->SendAll(player_confirm_packet);

	uint32_t locked_player_count = 0;
	for (auto& player : game->players) {
		if (player.second.second) {
			locked_player_count += 1;
		}
	}
	if (locked_player_count == 4) {
		auto play_next_scene_packet = std::make_shared<Packet>(PacketType::PlayNextScene);
		uint32_t scene_id = 1;
		*play_next_scene_packet << scene_id;
		game->SendAll(play_next_scene_packet);
		game->PlayScene(scene_id);
	}
}

void Lobby::Render(sf::RenderWindow& window) {
	window.draw(text);
}

void Lobby::OnConnect(uint32_t connection_id) {
}

void Lobby::OnDisconnect(uint32_t connection_id) {

}

bool Lobby::ProcessPacket(std::shared_ptr<Packet> packet) {
	switch (packet->GetPacketType()) {
	case PacketType::PlayerPick: {
		uint32_t player_id;
		uint32_t client_id;
		*packet >> player_id >> client_id;

		for (auto& player : game->players) {
			if (player.second.second == true) {
				continue;
			}

			if (player.second.first == client_id) {
				player.second.first = 0;
			}
		}

		for (auto& player : game->players) {
			if (player.second.second == true) {
				continue;
			}

			if (player.first == player_id) {
				player.second.first = client_id;
			}
		}

		return true;
	}

	case PacketType::PlayerLock: {
		uint32_t client_id;
		*packet >> client_id;

		for (auto& player : game->players) {
			if (player.second.first == client_id) {
				player.second.second = true;
			}
		}

		return true;
	}

	default: {
		return false;
	}

	}
}
