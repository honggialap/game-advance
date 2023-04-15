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

	state = State::Picking;
	count_down = 1000;

	for (uint32_t i = 1; i <= game->open_slots; i++) {
		game->players[i] = std::make_pair(uint32_t(0), false);
	}

}

void Lobby::Unload() {
}

void Lobby::Update(float elapsed) {
	switch (state) {

	case Lobby::Picking: {
		std::stringstream displaying;
		displaying << "PLAYER\n";
		for (auto& player : game->players) {
			uint32_t player_id = player.first;
			uint32_t client_id = player.second.first;
			bool locked = player.second.second;
			std::string status = locked ? "LOCKED" : "PICKING";
			displaying << player_id << " : " << client_id << " : " << status << "\n";
		}
		text.setString(displaying.str());

		SendConfirmPacket();

		uint32_t locked_player = 0;
		for (auto& player : game->players) {
			if (player.second.second) {
				locked_player += 1;
			}
		}
		if (locked_player == game->open_slots) {
			state = State::Locked;
		}
		break;
	}

	case Lobby::Locked: {
		std::stringstream displaying;
		displaying << "READY: " << count_down;
		text.setString(displaying.str());
		if (count_down > 0) {
			count_down -= elapsed;
		}
		else {
			SendNextScenePacket(uint32_t(1));
			game->PlayScene(uint32_t(1));
		}
		break;
	}

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
		uint32_t player_id = 0;
		uint32_t client_id = 0;
		*packet >> player_id >> client_id;
		SetPlayerPick(player_id, client_id);
		return true;
	}

	case PacketType::PlayerLock: {
		uint32_t client_id = 0;
		*packet >> client_id;
		SetPlayerLock(client_id);
		return true;
	}

	default: {
		return false;
	}

	}
}

void Lobby::SendConfirmPacket() {
	auto player_confirm_packet = std::make_shared<Packet>(PacketType::PlayerConfirm);
	
	uint32_t total_player = game->players.size();
	*player_confirm_packet << total_player;

	for (auto& player : game->players) {
		uint32_t player_id = player.first;
		uint32_t client_id = player.second.first;
		bool locked = player.second.second;

		*player_confirm_packet << player_id << client_id << locked;
	}

	game->SendAll(player_confirm_packet);
}

void Lobby::SendNextScenePacket(uint32_t scene_id) {
	auto next_scene_packet = std::make_shared<Packet>(PacketType::PlayNextScene);
	uint32_t next_scene_id = scene_id;
	*next_scene_packet << next_scene_id;
	game->SendAll(next_scene_packet);
}

void Lobby::SetPlayerPick(uint32_t player_id, uint32_t client_id) {
	for (auto& player : game->players) {
		if (player.second.second) {
			continue;
		}

		if (player.second.first == client_id) {
			player.second.first = uint32_t(0);
		}
	}

	for (auto& player : game->players) {
		if (player.second.second) {
			continue;
		}

		if (player.first == player_id) {
			player.second.first = client_id;
		}
	}
}

void Lobby::SetPlayerLock(uint32_t client_id) {
	for (auto& player : game->players) {
		if (player.second.first == client_id) {
			player.second.second = true;
		}
	}
}