#include "client/core/main_scene.h"
#include "client/core/game.h"

#include "client/actor/game_master.h"
#include "client/actor/player_tank.h"
#include "client/actor/player_bullet.h"
#include "client/actor/creep_tank.h"
#include "client/actor/creep_bullet.h"
#include "client/actor/turret.h"
#include "client/actor/turret_bullet.h"
#include "client/actor/headquarter.h"
#include "client/actor/factory.h"
#include "client/actor/repair_kit.h"
#include "client/actor/power_up.h"
#include "client/actor/bound.h"
#include "client/actor/wall.h"
#include "client/actor/tree.h"
#include "client/actor/water.h"

namespace NSClient {
	namespace NSCore {

		CMainScene::CMainScene(NSEngine::NSCore::pGame game)
			: NSClient::NSCore::CScene(game) {
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

			font.loadFromFile("data/resources/fonts/arial.ttf");
			text.setFont(font);

			world = new CWorld(game);
		}

		void CMainScene::Unload() {
			if (world) {
				world->game_objects.clear();
				delete world;
				world = nullptr;
			}
		}

		void CMainScene::Update(float elapsed) {
			switch (state) {
			case CMainScene::EState::Loading:
				if (!ready_sent) {
					SendReadyPacket();
					ready_sent = true;
				}
				break;

			case CMainScene::EState::Run: {
				if (world->IsJustGotGameState()) {
					world->SetJustGotGameState(false);
					for (uint32_t reconcilate_tick = world->GetServerTick() + 1;
						reconcilate_tick < world->latest_tick;
						reconcilate_tick++) {

						world->Step(reconcilate_tick, elapsed);
					}
				}

				world->HandleInput(world->latest_tick);
				world->Step(world->latest_tick, elapsed);
				world->TrimCommands(128);

				if (!ping_sent) {
					SendPingPacket();
					ping_sent = true;
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

		void CMainScene::OnConnect() {

		}

		void CMainScene::OnDisconnect() {

		}

		void CMainScene::OnConnectFail() {

		}

		bool CMainScene::ProcessPacket(std::shared_ptr<NSEngine::NSNetworks::CPacket> packet) {
			switch (packet->GetPacketType()) {

			case NSEngine::EPacketType::SERVER_LOAD: {
				uint32_t game_object_count = 0;
				*packet >> game_object_count;

				for (uint32_t i = 0; i < game_object_count; i++) {

					uint32_t type;
					*packet >> type;

					std::string name;
					*packet >> name;

					NSEngine::NSCore::pGameObject game_object = nullptr;
					switch (NSEngine::EActorType(type)) {

					case NSEngine::EActorType::GAME_MASTER: {
						game_object = NSClient::NSActor::CGameMaster::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::PLAYER_TANK: {
						game_object = NSClient::NSActor::CPlayerTank::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::PLAYER_BULLET: {
						game_object = NSClient::NSActor::CPlayerBullet::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::CREEP_TANK: {
						game_object = NSClient::NSActor::CCreepTank::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::CREEP_BULLET: {
						game_object = NSClient::NSActor::CCreepBullet::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::TURRET: {
						game_object = NSClient::NSActor::CTurret::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::TURRET_BULLET: {
						game_object = NSClient::NSActor::CTurretBullet::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::HEADQUARTER: {
						game_object = NSClient::NSActor::CPlayerTank::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::FACTORY: {
						game_object = NSClient::NSActor::CFactory::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::REPAIR_KIT: {
						game_object = NSClient::NSActor::CRepairKit::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::POWER_UP: {
						game_object = NSClient::NSActor::CPowerUp::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::BOUND: {
						game_object = NSClient::NSActor::CBound::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::WALL: {
						game_object = NSClient::NSActor::CWall::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::TREE: {
						game_object = NSClient::NSActor::CTree::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::WATER: {
						game_object = NSClient::NSActor::CWater::Create(game, world, name);
						break;
					}

					}

					if (game_object) {
						if (dynamic_cast<NSEngine::NSComponent::pNetworksLoadable>(game_object)) {
							dynamic_cast<NSEngine::NSComponent::pNetworksLoadable>(game_object)->UnpackNetworksLoadPacket(packet.get());					
						}
					}

				}

				SendLoadPacket();

				return true;
			}

			case NSEngine::EPacketType::START_GAME: {
				state = EState::Run;
				return true;
			}

			case NSEngine::EPacketType::PING: {
				uint32_t reply_ping_tick;
				*packet >> reply_ping_tick;
				ping_tick = (world->latest_tick - reply_ping_tick) / 2;
				ping_sent = false;
				return true;
			}

			case NSEngine::EPacketType::SERVER_GAME_STATE: {
				world->SetJustGotGameState(true);

				uint32_t server_tick = 0;
				*packet >> server_tick;
				world->SetServerTick(server_tick);

				uint32_t game_object_count = 0;
				*packet >> game_object_count;
				for (uint32_t i = 0; i < game_object_count; i++) {
					uint32_t type = 0;
					*packet >> type;

					uint32_t id = 0;
					*packet >> id;

					auto game_object = world->game_objects[id].get();
					if (dynamic_cast<NSEngine::NSComponent::pRecordable>(game_object)) {
						auto recordable = dynamic_cast<NSEngine::NSComponent::pRecordable>(game_object);
						auto record = recordable->UnpackRecord(packet.get());
						recordable->Deserialize(record);
						delete record;
					}
				}
				return true;
			}

			case NSEngine::EPacketType::PLAYER_MOVE: {
				uint32_t tick;
				uint32_t game_object_id;
				uint32_t command_type;
				int32_t x;
				int32_t y;

				*packet
					>> tick
					>> game_object_id
					>> command_type
					>> x
					>> y
					;

				NSEngine::NSActor::CMoveCommand move_command(game_object_id, x, y);
				world->commands[tick].push_back(
					std::make_unique<NSEngine::NSActor::CMoveCommand>(move_command)
				);

				return true;
			}

			default: {
				return false;
			}

			}
		}

		void CMainScene::SendReadyPacket() {
			auto ready_packet = std::make_shared<NSEngine::NSNetworks::CPacket>(NSEngine::EPacketType::CLIENT_READY);
			game_client->Send(ready_packet);
		}

		void CMainScene::SendLoadPacket() {
			auto client_load_packet = std::make_shared<NSEngine::NSNetworks::CPacket>(NSEngine::EPacketType::CLIENT_LOAD);
			game_client->Send(client_load_packet);
		}

		void CMainScene::SendPingPacket() {
			auto ping_packet = std::make_shared<NSEngine::NSNetworks::CPacket>(NSEngine::EPacketType::PING);
			*ping_packet
				<< game_client->GetClientId()
				<< game_client->GetPlayerId()
				<< world->latest_tick
				<< ping_tick
				;
			game_client->Send(ping_packet);
			ping_sent = true;
		}

	}
}