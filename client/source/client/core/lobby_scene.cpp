#include "client/core/lobby_scene.h"
#include "client/core/game.h"

namespace NSClient {
	namespace NSCore {

		CLobbyScene::CLobbyScene(NSEngine::NSCore::pGame game)
			: NSClient::NSCore::CScene(game) {
		}

		CLobbyScene::~CLobbyScene() {
		}

		void CLobbyScene::Load(std::string data_path) {
			std::ifstream data_file(data_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

			font.loadFromFile("data/resources/fonts/arial.ttf");
			text.setFont(font);

			state = EState::Connecting;
			pick_sent = false;
			lockable = false;
		}

		void CLobbyScene::Unload() {
		}

		void CLobbyScene::Update(float elapsed) {
			switch (state) {

			case CLobbyScene::EState::Connecting: {
				text.setString("PRESS SPACE TO CONNECT TO SERVER !");
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					game_client->Connect();
				}
			}

			case CLobbyScene::EState::Picking: {
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

			case CLobbyScene::EState::Locked: {
				text.setString("WAITING FOR OTHER PLAYERS\n");
				break;
			}

			}
		}

		void CLobbyScene::Render(sf::RenderWindow& window) {
			window.draw(text);
		}

		void CLobbyScene::OnConnect() {
			state = Picking;
		}

		void CLobbyScene::OnDisconnect() {
			state = Connecting;
		}

		void CLobbyScene::OnConnectFail() {
			state = Connecting;
		}

		bool CLobbyScene::ProcessPacket(std::shared_ptr<NSEngine::NSNetworks::CPacket> packet) {
			switch (packet->GetPacketType()) {
			case NSEngine::EPacketType::PLAYER_CONFIRM: {
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
						state = EState::Locked;
					}

					std::string status = locked ? "LOCKED" : "PICKING";
					displaying << player_id << " : " << client_id << " : " << status << "\n";
				}

				text.setString(displaying.str());
				return true;
			}

			case NSEngine::EPacketType::PLAY_NEXT_SCENE: {
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

		void CLobbyScene::SendPickPacket(uint32_t player_id) {
			auto pick_packet = std::make_shared<NSEngine::NSNetworks::CPacket>(NSEngine::EPacketType::PLAYER_PICK);
			*pick_packet << player_id << game_client->GetClientId();
			game_client->Send(pick_packet);
		}

		void CLobbyScene::SendLockPacket() {
			auto lock_packet = std::make_shared<NSEngine::NSNetworks::CPacket>(NSEngine::EPacketType::PLAYER_LOCK);
			*lock_packet << game_client->GetClientId();
			game_client->Send(lock_packet);
		}

	}
}
