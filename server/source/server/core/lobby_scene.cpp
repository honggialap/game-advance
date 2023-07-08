#include "server/core/lobby_scene.h"
#include "server/core/game.h"

namespace NSServer {
	namespace NSCore {

		CLobbyScene::CLobbyScene(NSEngine::NSCore::pGame game)
			: NSServer::NSCore::CScene(game) {
		}

		CLobbyScene::~CLobbyScene() {
		}

		void CLobbyScene::Load(std::string data_path) {
			std::ifstream data_file(data_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

			std::string texture_source = data.at("texture");
			texture.loadFromFile(texture_source);
			sprite.setTexture(texture);
			sprite.setPosition(sf::Vector2f(0.0f, 0.0f));

			std::string font_source = data.at("font");
			font.loadFromFile(font_source);
			text.setFont(font);
			text.setPosition(sf::Vector2f(
				game->GetWindow().getSize().x / 2.0f
				, game->GetWindow().getSize().y / 3.0f * 2.0f
			));

			state = EState::Picking;
			count_down = 1000;

			for (uint32_t i = 1; i <= game_server->GetMaxConnectionLimit(); i++) {
				game_server->players[i] = std::make_pair(uint32_t(0), false);
			}

		}

		void CLobbyScene::Unload() {
		}

		void CLobbyScene::Update(float elapsed) {
			switch (state) {

			case CLobbyScene::EState::Picking: {
				std::stringstream displaying;
				displaying << "PLAYER\n";
				for (auto& player : game_server->players) {
					uint32_t player_id = player.first;
					uint32_t client_id = player.second.first;
					bool locked = player.second.second;
					std::string status = locked ? "LOCKED" : "PICKING";
					displaying << player_id << " : " << client_id << " : " << status << "\n";
				}
				text.setString(displaying.str());

				SendConfirmPacket();

				uint32_t locked_player = 0;
				for (auto& player : game_server->players) {
					if (player.second.second) {
						locked_player += 1;
					}
				}
				if (locked_player == game_server->GetMaxConnectionLimit()) {
					state = EState::Locked;
				}
				break;
			}

			case CLobbyScene::EState::Locked: {
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

		void CLobbyScene::Render(sf::RenderWindow& window) {
			text.setOrigin(
				text.getLocalBounds().width / 2.0f
				, text.getLocalBounds().height / 2.0f
			);

			window.draw(sprite);
			window.draw(text);
		}

		void CLobbyScene::OnConnect(uint32_t connection_id) {
		}

		void CLobbyScene::OnDisconnect(uint32_t connection_id) {
		}

		bool CLobbyScene::ProcessPacket(std::shared_ptr<NSEngine::NSNetworks::CPacket> packet) {
			switch (packet->GetPacketType()) {
			case NSEngine::EPacketType::PLAYER_PICK: {
				uint32_t player_id = 0;
				uint32_t client_id = 0;
				*packet >> player_id >> client_id;
				SetPlayerPick(player_id, client_id);
				return true;
			}

			case NSEngine::EPacketType::PLAYER_LOCK: {
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

		void CLobbyScene::SendConfirmPacket() {
			auto player_confirm_packet = std::make_shared<NSEngine::NSNetworks::CPacket>(NSEngine::EPacketType::PLAYER_CONFIRM);

			uint32_t total_player = game_server->players.size();
			*player_confirm_packet << total_player;

			for (auto& player : game_server->players) {
				uint32_t player_id = player.first;
				uint32_t client_id = player.second.first;
				bool locked = player.second.second;

				*player_confirm_packet << player_id << client_id << locked;
			}

			game_server->SendAll(player_confirm_packet);
		}

		void CLobbyScene::SendNextScenePacket(uint32_t scene_id) {
			auto next_scene_packet = std::make_shared<NSEngine::NSNetworks::CPacket>(NSEngine::EPacketType::PLAY_NEXT_SCENE);
			uint32_t next_scene_id = scene_id;
			*next_scene_packet << next_scene_id;
			game_server->SendAll(next_scene_packet);
		}

		void CLobbyScene::SetPlayerPick(uint32_t player_id, uint32_t client_id) {
			for (auto& player : game_server->players) {
				if (player.second.second) {
					continue;
				}

				if (player.second.first == client_id) {
					player.second.first = uint32_t(0);
				}
			}

			for (auto& player : game_server->players) {
				if (player.second.second) {
					continue;
				}

				if (player.first == player_id) {
					player.second.first = client_id;
				}
			}
		}

		void CLobbyScene::SetPlayerLock(uint32_t client_id) {
			for (auto& player : game_server->players) {
				if (player.second.first == client_id) {
					player.second.second = true;
				}
			}
		}

	}
}