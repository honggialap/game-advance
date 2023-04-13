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

	picked = false;
	locked = false;
}

void Lobby::Unload() {
}

void Lobby::Update(float elapsed) {
	if (!picked && !locked) {
		// this should be fix
		// cause of the real-time keyboard state reading of sfml
		// and multiple client instance running on the same machine
		switch (game->GetId()) {
		case 1000: {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
				auto picking_packet = std::make_shared<Packet>(PlayerPick);
				*picking_packet << uint32_t(1) << game->GetId();
				game->Send(picking_packet);
				picked = true;
			} 
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
				auto picking_packet = std::make_shared<Packet>(PlayerPick);
				*picking_packet << uint32_t(2) << game->GetId();
				game->Send(picking_packet);
				picked = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
				auto picking_packet = std::make_shared<Packet>(PlayerPick);
				*picking_packet << uint32_t(3) << game->GetId();
				game->Send(picking_packet);
				picked = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
				auto picking_packet = std::make_shared<Packet>(PlayerPick);
				*picking_packet << uint32_t(4) << game->GetId();
				game->Send(picking_packet);
				picked = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
				if (game->player_id != 0) {
					auto locking_packet = std::make_shared<Packet>(PlayerLock);
					*locking_packet << game->GetId();
					game->Send(locking_packet);
					picked = true;
				}
			}
			break;
		}

		case 1001: {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
				auto picking_packet = std::make_shared<Packet>(PlayerPick);
				*picking_packet << uint32_t(1) << game->GetId();
				game->Send(picking_packet);
				picked = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				auto picking_packet = std::make_shared<Packet>(PlayerPick);
				*picking_packet << uint32_t(2) << game->GetId();
				game->Send(picking_packet);
				picked = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
				auto picking_packet = std::make_shared<Packet>(PlayerPick);
				*picking_packet << uint32_t(3) << game->GetId();
				game->Send(picking_packet);
				picked = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				auto picking_packet = std::make_shared<Packet>(PlayerPick);
				*picking_packet << uint32_t(4) << game->GetId();
				game->Send(picking_packet);
				picked = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
				if (game->player_id != 0) {
					auto locking_packet = std::make_shared<Packet>(PlayerLock);
					*locking_packet << game->GetId();
					game->Send(locking_packet);
					picked = true;
				}
			}
			break;
		}

		case 1002: {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				auto picking_packet = std::make_shared<Packet>(PlayerPick);
				*picking_packet << uint32_t(1) << game->GetId();
				game->Send(picking_packet);
				picked = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				auto picking_packet = std::make_shared<Packet>(PlayerPick);
				*picking_packet << uint32_t(2) << game->GetId();
				game->Send(picking_packet);
				picked = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				auto picking_packet = std::make_shared<Packet>(PlayerPick);
				*picking_packet << uint32_t(3) << game->GetId();
				game->Send(picking_packet);
				picked = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
				auto picking_packet = std::make_shared<Packet>(PlayerPick);
				*picking_packet << uint32_t(4) << game->GetId();
				game->Send(picking_packet);
				picked = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
				if (game->player_id != 0) {
					auto locking_packet = std::make_shared<Packet>(PlayerLock);
					*locking_packet << game->GetId();
					game->Send(locking_packet);
					picked = true;
				}
			}
			break;
		}

		case 1003: {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
				auto picking_packet = std::make_shared<Packet>(PlayerPick);
				*picking_packet << uint32_t(1) << game->GetId();
				game->Send(picking_packet);
				picked = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
				auto picking_packet = std::make_shared<Packet>(PlayerPick);
				*picking_packet << uint32_t(2) << game->GetId();
				game->Send(picking_packet);
				picked = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
				auto picking_packet = std::make_shared<Packet>(PlayerPick);
				*picking_packet << uint32_t(3) << game->GetId();
				game->Send(picking_packet);
				picked = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
				auto picking_packet = std::make_shared<Packet>(PlayerPick);
				*picking_packet << uint32_t(4) << game->GetId();
				game->Send(picking_packet);
				picked = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
				if (game->player_id != 0) {
					auto locking_packet = std::make_shared<Packet>(PlayerLock);
					*locking_packet << game->GetId();
					game->Send(locking_packet);
					picked = true;
				}
			}
			break;
		}

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
		std::stringstream displaying;
		displaying << "PLAYERS\n";

		uint32_t player_count = 0;
		*packet >> player_count;

		game->player_id = 0;
		
		for (uint32_t i = 1; i <= player_count; i++) {
			uint32_t player_id = 0;
			uint32_t client_id = 0;
			bool player_status = false;
			*packet >> player_id >> client_id >> player_status;

			if (game->GetId() == client_id) {
				game->player_id = player_id;
				if (player_status) {
					locked = true;
				}
			}

			std::string status = player_status ? "LOCKED" : "PICKING";
			displaying << player_id << " : " << client_id <<  " : " << status << "\n";
		}

		text.setString(displaying.str());
		picked = false;
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
