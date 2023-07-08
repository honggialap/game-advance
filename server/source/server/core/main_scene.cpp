#include "server/core/main_scene.h"
#include "server/core/game.h"

#include "server/actor/game_master.h"
#include "server/actor/headquarter.h"

#include "server/actor/tank/player_tank.h"
#include "server/actor/tank/basic_tank.h"
#include "server/actor/tank/fast_tank.h"
#include "server/actor/tank/power_tank.h"
#include "server/actor/tank/armor_tank.h"
#include "server/actor/tank/bullet.h"

#include "server/actor/power_up/grenade.h"
#include "server/actor/power_up/helmet.h"
#include "server/actor/power_up/shovel.h"
#include "server/actor/power_up/star.h"
#include "server/actor/power_up/tank.h"
#include "server/actor/power_up/timer.h"

#include "server/actor/terrain/bound.h"
#include "server/actor/terrain/brick.h"
#include "server/actor/terrain/ice.h"
#include "server/actor/terrain/steel.h"
#include "server/actor/terrain/tree.h"
#include "server/actor/terrain/water.h"

#include "server/actor/effect/explosion.h"
#include "server/actor/effect/impact.h"
#include "server/actor/effect/score.h"


namespace NSServer {
	namespace NSCore {

		CMainScene::CMainScene(NSEngine::NSCore::pGame game)
			: NSServer::NSCore::CScene(game) {
		}

		CMainScene::~CMainScene() {
		}

		void CMainScene::Load(std::string data_path) {
			std::ifstream data_file(data_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

			float window_width = (float)game->GetWindow().getSize().x;
			float window_height = (float)game->GetWindow().getSize().y;
			camera.reset(sf::FloatRect(0, 0, window_width, window_height));
			camera.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

			font.loadFromFile("data/resource/font/arial.ttf");
			text.setFont(font);

			world = new CWorld(game);
			world->Load(data.at("world"));

			for (uint32_t i = 1; i <= game_server->GetMaxConnectionLimit(); i++) {
				player_ping[i] = 0;
			}
		}

		void CMainScene::Unload() {
			if (world) {
				world->Unload();
				delete world;
				world = nullptr;
			}

			player_ping.clear();
		}

		void CMainScene::Update(float elapsed) {
			switch (state) {
			case CMainScene::EState::Loading: {
				break;
			}

			case CMainScene::EState::Run: {
				if (world->IsRollback()) {
					uint32_t last_tick = world->latest_tick - 1;
					uint32_t deserialize_tick = world->GetRollbackTick() - 1;

					world->TrimRecords(deserialize_tick, last_tick);
					world->Deserialize(deserialize_tick);

					for (uint32_t rollback_tick = world->GetRollbackTick();
						rollback_tick <= last_tick;
						rollback_tick++) {

						world->Step(rollback_tick, elapsed);
						world->Serialize(rollback_tick);
					}

					world->SetRollback(false);
					world->SetRollbackTick(last_tick);
				}

				world->HandleInput(world->latest_tick);
				world->Step(world->latest_tick, elapsed);
				world->Serialize(world->latest_tick);

				world->TrimCommands(64);
				world->TrimRecords(64);

				if (world->latest_tick > world->tick_per_game_state
					&& world->latest_tick % world->tick_per_game_state == 0) {
					SendGameStatePacket();
				}

				world->latest_tick += 1;
				break;
			}
			}
		}

		void CMainScene::Render(sf::RenderWindow& window) {
			window.setView(camera);
			window.draw(text);

			switch (state) {
			case CMainScene::EState::Loading: {
				break;
			}

			case CMainScene::EState::Run: {
				world->Render(window);
				break;
			}
			}
		}

		sf::View& CMainScene::GetCamera() {
			return camera;
		}

		void CMainScene::OnConnect(uint32_t connection_id) {

		}

		void CMainScene::OnDisconnect(uint32_t connection_id) {

		}

		bool CMainScene::ProcessPacket(std::shared_ptr<NSEngine::NSNetworks::CPacket> packet) {
			switch (packet->GetPacketType()) {
			case NSEngine::EPacketType::CLIENT_READY: {
				ready_client_count += 1;
				if (ready_client_count == game_server->GetMaxConnectionLimit()) {
					SendLoadPacket();
				}
				return true;
			}

			case NSEngine::EPacketType::CLIENT_LOAD: {
				load_client_count += 1;
				if (load_client_count == game_server->GetMaxConnectionLimit()) {
					state = EState::Run;
					SendStartGamePacket();
				}
				return true;
			}

			case NSEngine::EPacketType::PING: {
				uint32_t client_id = 0;
				uint32_t player_id = 0;
				uint32_t reply_ping_tick = 0;
				uint32_t ping = 0;

				*packet
					>> client_id
					>> player_id
					>> reply_ping_tick
					>> ping
					;

				player_ping[player_id] = ping;

				SendReplyPingPacket(client_id, reply_ping_tick);
				return true;
			}

			case NSEngine::EPacketType::PLAYER_MOVE: {
				uint32_t client_id;
				uint32_t player_id;
				uint32_t tick;
				uint32_t game_object_id;
				uint32_t command_type;
				int32_t x;
				int32_t y;

				*packet
					>> client_id
					>> player_id
					>> tick
					>> game_object_id
					>> command_type
					>> x
					>> y
					;

				if (tick < world->latest_tick - (world->tick_per_game_state * 2)) {
					return true;
				}

				world->commands[tick].push_back(
					std::make_unique<NSEngine::NSActor::CMoveCommand>(game_object_id, x, y)
				);

				if (tick < world->latest_tick) {
					world->SetRollback(true);
					if (world->GetRollbackTick() > tick) {
						world->SetRollbackTick(tick);
					}
				}

				return true;
			}

			default: {
				return false;
			}

			}
		}

		void CMainScene::SendLoadPacket() {
			auto server_load_packet = std::make_shared<NSEngine::NSNetworks::CPacket>(NSEngine::EPacketType::SERVER_LOAD);

			uint32_t game_objects_count = world->game_objects.size();
			*server_load_packet << game_objects_count;

			for (auto& game_object_container : world->game_objects) {
				NSEngine::NSCore::pGameObject game_object = game_object_container.second.get();

				uint32_t type = game_object->GetType();
				*server_load_packet << type;

				std::string name = game_object->GetName();
				*server_load_packet << name;

				game_object->PackLoadPacket(server_load_packet.get());
			}

			game_server->SendAll(server_load_packet);
		}

		void CMainScene::SendStartGamePacket() {
			auto start_game_packet = std::make_shared<NSEngine::NSNetworks::CPacket>(NSEngine::EPacketType::START_GAME);
			game_server->SendAll(start_game_packet);
		}

		void CMainScene::SendGameStatePacket() {
			auto& records = world->records[world->latest_tick - world->tick_per_game_state];

			auto game_state_packet = std::make_shared<NSEngine::NSNetworks::CPacket>(NSEngine::EPacketType::SERVER_GAME_STATE);

			uint32_t server_tick = world->latest_tick - world->tick_per_game_state;
			*game_state_packet << server_tick;

			uint32_t game_object_count = records.size();
			*game_state_packet << game_object_count;

			for (auto& record : records) {
				uint32_t type = record->actor_type;
				*game_state_packet << type;

				uint32_t id = record->game_object_id;
				*game_state_packet << id;

				NSEngine::NSCore::pGameObject game_object = world->game_objects[id].get();
				if (dynamic_cast<NSEngine::NSComponent::pRecordable>(game_object)) {
					auto recordable = dynamic_cast<NSEngine::NSComponent::pRecordable>(game_object);
					recordable->PackRecord(game_state_packet.get(), record.get());
				}

			}

			game_server->SendAll(game_state_packet);
		}

		void CMainScene::SendReplyPingPacket(uint32_t client_id, uint32_t reply_ping_tick) {
			auto ping_reply_packet = std::make_shared<NSEngine::NSNetworks::CPacket>(NSEngine::EPacketType::PING);
			*ping_reply_packet << reply_ping_tick;
			game_server->Send(client_id, ping_reply_packet);
		}

	}
}
