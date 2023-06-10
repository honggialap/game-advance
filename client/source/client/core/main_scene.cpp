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

					switch (NSEngine::EActorType(type)) {

					case NSEngine::EActorType::GAME_MASTER: {
						
						std::string resource_path;
						*packet >> resource_path;

						auto game_master = NSClient::NSActor::CGameMaster::Create(
							game, world, name,
							resource_path
						);
						break;
					}

					case NSEngine::EActorType::PLAYER_TANK: {
						
						float position_x, position_y;
						*packet >> position_x >> position_y;

						uint32_t layer;
						*packet >> layer;

						std::string data_path;
						*packet >> data_path;

						uint32_t player_id;
						*packet >> player_id;

						uint32_t team;
						*packet >> team;

						auto tank = NSClient::NSActor::CPlayerTank::Create(game, world, name, data_path);
						tank->SetPlayerId(player_id);
						if (tank->GetPlayerId() == game_client->GetPlayerId()) {
							tank->SetPlayerControl(true);
						}
						break;
					}

					case NSEngine::EActorType::PLAYER_BULLET: {
						std::string name;
						*packet >> name;

						float position_x, position_y;
						*packet >> position_x >> position_y;

						uint32_t layer;
						*packet >> layer;

						std::string data_path;
						*packet >> data_path;

						uint32_t team;
						*packet >> team;

						auto player_bullet = NSClient::NSActor::CPlayerBullet::Create(game, world, name, data_path);
						break;
					}

					case NSEngine::EActorType::CREEP_TANK: {
						std::string name;
						*packet >> name;

						float position_x, position_y;
						*packet >> position_x >> position_y;

						uint32_t layer;
						*packet >> layer;

						std::string data_path;
						*packet >> data_path;

						uint32_t team;
						*packet >> team;

						auto creep_tank = NSClient::NSActor::CCreepTank::Create(game, world, name, data_path);
						break;
					}

					case NSEngine::EActorType::CREEP_BULLET: {
						std::string name;
						*packet >> name;

						float position_x, position_y;
						*packet >> position_x >> position_y;

						uint32_t layer;
						*packet >> layer;

						std::string data_path;
						*packet >> data_path;

						uint32_t team;
						*packet >> team;

						auto creep_bullet = NSClient::NSActor::CCreepBullet::Create(game, world, name, data_path);
						break;
					}

					case NSEngine::EActorType::TURRET: {
						std::string name;
						*packet >> name;

						float position_x, position_y;
						*packet >> position_x >> position_y;

						uint32_t layer;
						*packet >> layer;

						std::string data_path;
						*packet >> data_path;

						uint32_t team;
						*packet >> team;

						auto turret = NSClient::NSActor::CTurret::Create(game, world, name, data_path);
						break;
					}

					case NSEngine::EActorType::TURRET_BULLET: {
						std::string name;
						*packet >> name;

						float position_x, position_y;
						*packet >> position_x >> position_y;

						uint32_t layer;
						*packet >> layer;

						std::string data_path;
						*packet >> data_path;

						uint32_t team;
						*packet >> team;

						auto turret_bullet = NSClient::NSActor::CTurretBullet::Create(game, world, name, data_path);
						break;
					}

					case NSEngine::EActorType::HEADQUARTER: {
						std::string name;
						*packet >> name;

						float position_x, position_y;
						*packet >> position_x >> position_y;

						uint32_t layer;
						*packet >> layer;

						std::string data_path;
						*packet >> data_path;

						uint32_t team;
						*packet >> team;

						auto headquarter = NSClient::NSActor::CHeadquarter::Create(game, world, name, data_path);
						break;
					}

					case NSEngine::EActorType::FACTORY: {
						std::string name;
						*packet >> name;

						float position_x, position_y;
						*packet >> position_x >> position_y;

						uint32_t layer;
						*packet >> layer;

						std::string data_path;
						*packet >> data_path;

						uint32_t team;
						*packet >> team;

						auto factory = NSClient::NSActor::CFactory::Create(game, world, name, data_path);
						break;
					}

					case NSEngine::EActorType::REPAIR_KIT: {
						std::string name;
						*packet >> name;

						float position_x, position_y;
						*packet >> position_x >> position_y;

						uint32_t layer;
						*packet >> layer;

						std::string data_path;
						*packet >> data_path;

						auto repair_kit = NSClient::NSActor::CRepairKit::Create(game, world, name, data_path);
						break;
					}

					case NSEngine::EActorType::POWER_UP: {
						std::string name;
						*packet >> name;

						float position_x, position_y;
						*packet >> position_x >> position_y;

						uint32_t layer;
						*packet >> layer;

						std::string data_path;
						*packet >> data_path;

						auto power_up = NSClient::NSActor::CPowerUp::Create(game, world, name, data_path);
						break;
					}

					case NSEngine::EActorType::BOUND: {
						auto bound = NSClient::NSActor::CBound::Create(game, world, name);
						bound->UnpackLoadPhysics(packet.get());
						break;
					}

					case NSEngine::EActorType::WALL: {
						std::string name;
						*packet >> name;

						float position_x, position_y;
						*packet >> position_x >> position_y;

						uint32_t layer;
						*packet >> layer;

						std::string data_path;
						*packet >> data_path;

						auto wall = NSClient::NSActor::CWall::Create(game, world, name, data_path);
						break;
					}

					case NSEngine::EActorType::TREE: {
						std::string name;
						*packet >> name;

						float position_x, position_y;
						*packet >> position_x >> position_y;

						uint32_t layer;
						*packet >> layer;

						std::string data_path;
						*packet >> data_path;

						auto tree = NSClient::NSActor::CTree::Create(game, world, name, data_path);
						break;
					}

					case NSEngine::EActorType::WATER: {
						std::string name;
						*packet >> name;

						float position_x, position_y;
						*packet >> position_x >> position_y;

						uint32_t layer;
						*packet >> layer;

						std::string data_path;
						*packet >> data_path;

						auto water = NSClient::NSActor::CWater::Create(game, world, name, data_path);
						break;
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

					switch (NSEngine::EActorType(type)) {
					case NSEngine::EActorType::GAME_MASTER: {
						NSClient::NSActor::pGameMaster game_master = static_cast<NSClient::NSActor::pGameMaster>(world->game_objects[id].get());

						break;
					}

					case NSEngine::EActorType::PLAYER_TANK: {
						float position_x, position_y;
						*packet >> position_x >> position_y;

						float velocity_x, velocity_y;
						*packet >> velocity_x >> velocity_y;

						int32_t movement_x, movement_y;
						*packet >> movement_x >> movement_y;

						NSClient::NSActor::pPlayerTank player_tank = static_cast<NSClient::NSActor::pPlayerTank>(world->game_objects[id].get());
						player_tank->last_known_x = player_tank->latest_x;
						player_tank->last_known_y = player_tank->latest_y;
						player_tank->latest_x = position_x;
						player_tank->latest_y = position_y;

						player_tank->SetPosition(position_x, position_y);
						player_tank->SetVelocity(velocity_x, velocity_y);
						player_tank->SetMovement(movement_x, movement_y);

						break;
					}

					case NSEngine::EActorType::PLAYER_BULLET: {
						float position_x, position_y;
						*packet >> position_x >> position_y;

						float velocity_x, velocity_y;
						*packet >> velocity_x >> velocity_y;

						NSClient::NSActor::pPlayerBullet player_bullet = static_cast<NSClient::NSActor::pPlayerBullet>(world->game_objects[id].get());
						player_bullet->SetPosition(position_x, position_y);
						player_bullet->SetVelocity(velocity_x, velocity_y);

						break;
					}

					case NSEngine::EActorType::CREEP_TANK: {
						float position_x, position_y;
						*packet >> position_x >> position_y;

						float velocity_x, velocity_y;
						*packet >> velocity_x >> velocity_y;

						NSClient::NSActor::pCreepTank creep_tank = static_cast<NSClient::NSActor::pCreepTank>(world->game_objects[id].get());
						creep_tank->SetPosition(position_x, position_y);
						creep_tank->SetVelocity(velocity_x, velocity_y);

						break;
					}

					case NSEngine::EActorType::CREEP_BULLET: {
						float position_x, position_y;
						*packet >> position_x >> position_y;

						float velocity_x, velocity_y;
						*packet >> velocity_x >> velocity_y;

						NSClient::NSActor::pCreepBullet creep_bullet = static_cast<NSClient::NSActor::pCreepBullet>(world->game_objects[id].get());
						creep_bullet->SetPosition(position_x, position_y);
						creep_bullet->SetVelocity(velocity_x, velocity_y);

						break;
					}

					case NSEngine::EActorType::TURRET: {
						NSClient::NSActor::pTurret turret = static_cast<NSClient::NSActor::pTurret>(world->game_objects[id].get());

						break;
					}

					case NSEngine::EActorType::TURRET_BULLET: {
						float position_x, position_y;
						*packet >> position_x >> position_y;

						float velocity_x, velocity_y;
						*packet >> velocity_x >> velocity_y;

						NSClient::NSActor::pTurretBullet turret_bullet = static_cast<NSClient::NSActor::pTurretBullet>(world->game_objects[id].get());
						turret_bullet->SetPosition(position_x, position_y);
						turret_bullet->SetVelocity(velocity_x, velocity_y);

						break;
					}

					case NSEngine::EActorType::HEADQUARTER: {
						NSClient::NSActor::pHeadquarter headquarter = static_cast<NSClient::NSActor::pHeadquarter>(world->game_objects[id].get());

						break;
					}

					case NSEngine::EActorType::FACTORY: {
						NSClient::NSActor::pFactory factory = static_cast<NSClient::NSActor::pFactory>(world->game_objects[id].get());

						break;
					}

					case NSEngine::EActorType::REPAIR_KIT: {
						float position_x, position_y;
						*packet >> position_x >> position_y;

						NSClient::NSActor::pRepairKit repair_kit = static_cast<NSClient::NSActor::pRepairKit>(world->game_objects[id].get());
						repair_kit->SetPosition(position_x, position_y);

						break;
					}

					case NSEngine::EActorType::POWER_UP: {
						float position_x, position_y;
						*packet >> position_x >> position_y;

						NSClient::NSActor::pPowerUp power_up = static_cast<NSClient::NSActor::pPowerUp>(world->game_objects[id].get());
						power_up->SetPosition(position_x, position_y);

						break;
					}

					case NSEngine::EActorType::BOUND: {
						NSClient::NSActor::pBound bound = static_cast<NSClient::NSActor::pBound>(world->game_objects[id].get());

						break;
					}

					case NSEngine::EActorType::WALL: {
						NSClient::NSActor::pWall wall = static_cast<NSClient::NSActor::pWall>(world->game_objects[id].get());

						break;
					}

					case NSEngine::EActorType::TREE: {
						NSClient::NSActor::pTree tree = static_cast<NSClient::NSActor::pTree>(world->game_objects[id].get());

						break;
					}

					case NSEngine::EActorType::WATER: {
						NSClient::NSActor::pWater water = static_cast<NSClient::NSActor::pWater>(world->game_objects[id].get());

						break;
					}

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