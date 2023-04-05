#include "lobby.h"
#include "game.h"

Lobby::Lobby(pGame game) : Scene(game) {
	state = NotConnected;
}

Lobby::	~Lobby() {
}

void Lobby::Load(std::string data_path) {
	std::ifstream data_file(data_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	font.loadFromFile("data/resources/fonts/arial.ttf");
	text.setFont(font);
}

void Lobby::Unload() {
}

void Lobby::SetState(State next_state) {
	// Exit
	switch (state) {
	case Lobby::NotConnected: {
		break;
	}

	case Lobby::WaitingForConfirm: {
		break;
	}

	case Lobby::Ready: {
		break;
	}

	}

	state = next_state;

	// Entry
	switch (state) {
	case Lobby::NotConnected: {
		text.setString("Client not connected yet.");
		break;
	}

	case Lobby::WaitingForConfirm: {
		text.setString("Press SPACE to ready.");
		break;
	}

	case Lobby::Ready: {
		text.setString("Waiting for other players.");
		break;
	}

	}
}

void Lobby::Update(float elapsed) {
	switch (state) {
	case Lobby::NotConnected: {
		if (game->IsApproved()) {
			SetState(WaitingForConfirm);
		}
		break;
	}

	case Lobby::WaitingForConfirm: {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
			auto player_confirm_packet = std::make_shared<Packet>(PacketType::PlayerConfirm);
			game->Send(player_confirm_packet);

			SetState(Ready);
		}
		break;
	}

	case Lobby::Ready: {
		break;
	}

	}
}

void Lobby::Render(sf::RenderWindow& window) {
	window.draw(text);
}

void Lobby::OnConnect() {
}

void Lobby::OnDisconnect() {
}

void Lobby::OnConnectFail() {
}

bool Lobby::ProcessPacket(std::shared_ptr<Packet> packet) {
	switch (packet->GetPacketType()) {
	case StartGame: {
		uint32_t scene_id;
		*packet >> scene_id;
		game->PlayScene(scene_id);
		return true;
	}

	default: {
		return false;
	}

	}
}
