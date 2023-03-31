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
	//
}

void Lobby::Render(sf::RenderWindow& window) {
	//
}

void Lobby::OnConnect() {

}

void Lobby::OnDisconnect() {

}

void Lobby::OnConnectFail() {

}

bool Lobby::ProcessPacket(std::shared_ptr<Packet> packet) {
	return true;
}
