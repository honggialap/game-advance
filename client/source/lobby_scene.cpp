#include "lobby_scene.h"
#include "game_client.h"

LobbyScene::LobbyScene(pGame game)
	: ClientScene(game)
{}

LobbyScene::~LobbyScene() 
{}

void LobbyScene::Load(std::string data_path) {
	std::ifstream data_file(data_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	font.loadFromFile("data/resources/fonts/arial.ttf");
	text.setFont(font);

	state = State::Connecting;
	pick_sent = false;
	lockable = false;
}

void LobbyScene::Unload() {
}

void LobbyScene::Update(float elapsed) {
	switch (state) {

	case LobbyScene::Connecting: {
		text.setString("PRESS SPACE TO CONNECT TO SERVER !");
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			game_client->Connect();
		}
	}

	case LobbyScene::Picking: {
		if (!pick_sent) {
			if (game->GetWindow().hasFocus()) {
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
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
						SendLockPacket();
					}
				}
			}
		}

		break;
	}

	case LobbyScene::Locked: {
		text.setString("WAITING FOR OTHER PLAYERS\n");
		break;
	}

	}
}

void LobbyScene::Render(sf::RenderWindow& window) {
	window.draw(text);
}

void LobbyScene::OnConnect() {
	state = Picking;
}

void LobbyScene::OnDisconnect() {
	state = Connecting;
}

void LobbyScene::OnConnectFail() {
	state = Connecting;
}

bool LobbyScene::ProcessPacket(std::shared_ptr<Packet> packet) {
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

			if (client_id == game_client->GetClientId()) {
				game_client->SetPlayerId(player_id);
			}

			if (
				client_id == game_client->GetClientId()
				&& player_id == game_client->GetPlayerId()
				) {
				lockable = true;
			}

			if (
				client_id == game_client->GetClientId()
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

void LobbyScene::SendPickPacket(uint32_t player_id) {
	auto pick_packet = std::make_shared<Packet>(PacketType::PlayerPick);
	*pick_packet << player_id << game_client->GetClientId();
	game_client->Send(pick_packet);
}

void LobbyScene::SendLockPacket() {
	auto lock_packet = std::make_shared<Packet>(PacketType::PlayerLock);
	*lock_packet << game_client->GetClientId();
	game_client->Send(lock_packet);
}