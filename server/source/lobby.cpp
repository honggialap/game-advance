#include "lobby.h"
#include "game.h"

Lobby::Lobby(pGame game) : Scene(game) {
	ready_players = 0;
}

Lobby::~Lobby() {
}

void Lobby::Load(std::string data_path) {
	std::ifstream data_file(data_path);
	nlohmann::json data = nlohmann::json::parse(data_file);
}

void Lobby::Unload() {
	//
}

void Lobby::Update(float elapsed) {
	if (ready_players == 3) {
		auto start_game_packet = std::make_shared<Packet>(PacketType::StartGame);
		uint32_t scene_id = 1;
		*start_game_packet << scene_id;

		game->SendAll(start_game_packet);
		game->PlayScene(scene_id);
	}
}

void Lobby::Render(sf::RenderWindow& window) {
	//
}

void Lobby::OnConnect(uint32_t connection_id) {

}

void Lobby::OnDisconnect(uint32_t connection_id) {

}

bool Lobby::ProcessPacket(std::shared_ptr<Packet> packet) {
	switch (packet->GetPacketType()) {
	case PlayerConfirm: {
		ready_players += 1;
		return true;
	}

	default: {
		return false;
	}

	}
}
