#include "lobby.h"
#include "game.h"

Lobby::Lobby(pGame game) : Scene(game) {
}

Lobby::	~Lobby() {
}

void Lobby::Load(std::string data_path) {
	std::ifstream data_file(data_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	font.loadFromFile("data/resources/fonts/arial.ttf");
	text.setFont(font);

	state = State::Picking;
	pick_sent = false;
	lockable = false;
}

void Lobby::Unload() {
}

void Lobby::Update(float elapsed) {
	switch (state) {

	case Lobby::Picking: {
		if (!pick_sent) {
			switch (game->GetId()) {

			case 1000: {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
					SendPickPacket(1);
					pick_sent = true;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
					SendPickPacket(2);
					pick_sent = true;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
					SendPickPacket(3);
					pick_sent = true;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
					SendPickPacket(4);
					pick_sent = true;
				}
				if (lockable) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
						SendLockPacket();
					}
				}
				break;
			}

			case 1001: {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
					SendPickPacket(1);
					pick_sent = true;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
					SendPickPacket(2);
					pick_sent = true;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
					SendPickPacket(3);
					pick_sent = true;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
					SendPickPacket(4);
					pick_sent = true;
				}
				if (lockable) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
						SendLockPacket();
					}
				}
				break;
			}

			case 1002: {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					SendPickPacket(1);
					pick_sent = true;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
					SendPickPacket(2);
					pick_sent = true;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					SendPickPacket(3);
					pick_sent = true;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
					SendPickPacket(4);
					pick_sent = true;
				}
				if (lockable) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
						SendLockPacket();
					}
				}
				break;
			}

			case 1003: {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
					SendPickPacket(1);
					pick_sent = true;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
					SendPickPacket(2);
					pick_sent = true;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
					SendPickPacket(3);
					pick_sent = true;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
					SendPickPacket(4);
					pick_sent = true;
				}
				if (lockable) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
						SendLockPacket();
					}
				}
				break;
			}

			}
		}
		break;
	}

	case Lobby::Locked: {
		text.setString("WAITING FOR OTHER PLAYERS\n");
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
	case PacketType::PlayerConfirm: {
		lockable = false;
		pick_sent = false;

		std::stringstream displaying;
		displaying << "PICK A SLOT:\n";

		uint32_t total_player = 0;
		*packet >> total_player;
		for (uint32_t i = 0; i < total_player; i++) {
			uint32_t player_id = 0;
			uint32_t client_id = 0;
			bool locked = false;
			*packet >> player_id >> client_id >> locked;

			if (client_id == game->GetId()) {
				game->player_id = player_id;
			}

			if (
				client_id == game->GetId()
				&& player_id == game->player_id
				) {
				lockable = true;
			}

			if (
				client_id == game->GetId()
				&& locked
				) {
				state = State::Locked;
			}

			std::string status = locked ? "LOCKED" : "PICKING";
			displaying << player_id << " : " << client_id << " : " << status << "\n";
		}

		text.setString(displaying.str());
		return true;
	}

	case PacketType::PlayNextScene: {
		uint32_t scene_id = 0;
		*packet >> scene_id;
		game->PlayScene(scene_id);
		return true;
	}

	default: {
		return false;
	}

	}
}

void Lobby::SendPickPacket(uint32_t player_id) {
	auto pick_packet = std::make_shared<Packet>(PacketType::PlayerPick);
	*pick_packet << player_id << game->GetId();
	game->Send(pick_packet);
}

void Lobby::SendLockPacket() {
	auto lock_packet = std::make_shared<Packet>(PacketType::PlayerLock);
	*lock_packet << game->GetId();
	game->Send(lock_packet);
}