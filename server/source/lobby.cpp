#include "lobby.h"
#include "game.h"

void Lobby::Load(std::string data_path) {
	std::ifstream data_file(data_path);
	nlohmann::json data = nlohmann::json::parse(data_file);
}

void Lobby::Unload() {
	//
}

void Lobby::Update(float elapsed) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {
		game->PlayScene(1);
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
	return true;
}
