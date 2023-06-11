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
						auto game_master = NSClient::NSActor::CGameMaster::Create(game, world, name);
						game_master->UnpackLoad(packet.get());

						break;
					}

					case NSEngine::EActorType::PLAYER_TANK: {
						auto tank = NSClient::NSActor::CPlayerTank::Create(game, world, name);
						tank->UnpackLoad(packet.get());

						break;
					}

					case NSEngine::EActorType::PLAYER_BULLET: {
						auto player_bullet = NSClient::NSActor::CPlayerBullet::Create(game, world, name);
						player_bullet->UnpackLoad(packet.get());

						break;
					}

					case NSEngine::EActorType::CREEP_TANK: {
						auto creep_tank = NSClient::NSActor::CCreepTank::Create(game, world, name);
						creep_tank->UnpackLoad(packet.get());

						break;
					}

					case NSEngine::EActorType::CREEP_BULLET: {
						auto creep_bullet = NSClient::NSActor::CCreepBullet::Create(game, world, name);
						creep_bullet->UnpackLoad(packet.get());

						break;
					}

					case NSEngine::EActorType::TURRET: {
						auto turret = NSClient::NSActor::CTurret::Create(game, world, name);
						turret->UnpackLoad(packet.get()); 

						break;
					}

					case NSEngine::EActorType::TURRET_BULLET: {
						auto turret_bullet = NSClient::NSActor::CTurretBullet::Create(game, world, name);
						turret_bullet->UnpackLoad(packet.get()); 

						break;
					}

					case NSEngine::EActorType::HEADQUARTER: {
						auto tank = NSClient::NSActor::CPlayerTank::Create(game, world, name);
						tank->UnpackLoad(packet.get()); 
						
						break;
					}

					case NSEngine::EActorType::FACTORY: {
						auto factory = NSClient::NSActor::CFactory::Create(game, world, name);
						factory->UnpackLoad(packet.get()); 
						
						break;
					}

					case NSEngine::EActorType::REPAIR_KIT: {
						auto repair_kit = NSClient::NSActor::CRepairKit::Create(game, world, name);
						repair_kit->UnpackLoad(packet.get());

						break;
					}

					case NSEngine::EActorType::POWER_UP: {
						auto power_up = NSClient::NSActor::CPowerUp::Create(game, world, name);
						power_up->UnpackLoad(packet.get());

						break;
					}

					case NSEngine::EActorType::BOUND: {
						auto bound = NSClient::NSActor::CBound::Create(game, world, name);
						bound->UnpackLoad(packet.get());

						break;
					}

					case NSEngine::EActorType::WALL: {
						auto wall = NSClient::NSActor::CWall::Create(game, world, name);
						wall->UnpackLoad(packet.get());

						break;
					}

					case NSEngine::EActorType::TREE: {
						auto tree = NSClient::NSActor::CTree::Create(game, world, name);
						tree->UnpackLoad(packet.get());

						break;
					}

					case NSEngine::EActorType::WATER: {
						auto water = NSClient::NSActor::CWater::Create(game, world, name);
						water->UnpackLoad(packet.get());

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
						auto game_master = static_cast<NSClient::NSActor::pGameMaster>(world->game_objects[id].get());
						auto game_master_record = NSEngine::NSActor::CGameMasterRecord(id);

						game_master->UnpackRecord(packet.get(), &game_master_record);
						game_master->Deserialize(&game_master_record);

						break;
					}

					case NSEngine::EActorType::PLAYER_TANK: {
						auto player_tank = static_cast<NSClient::NSActor::pPlayerTank>(world->game_objects[id].get());
						auto player_tank_record = NSEngine::NSActor::CPlayerTankRecord(id);

						player_tank->UnpackRecord(packet.get(), &player_tank_record);
						player_tank->Deserialize(&player_tank_record);

						break;
					}

					case NSEngine::EActorType::PLAYER_BULLET: {
						auto player_bullet = static_cast<NSClient::NSActor::pPlayerBullet>(world->game_objects[id].get());
						auto player_bullet_record = NSEngine::NSActor::CPlayerBulletRecord(id);

						player_bullet->UnpackRecord(packet.get(), &player_bullet_record);
						player_bullet->Deserialize(&player_bullet_record);

						break;
					}

					case NSEngine::EActorType::CREEP_TANK: {
						auto creep_tank = static_cast<NSClient::NSActor::pCreepTank>(world->game_objects[id].get());
						auto creep_tank_record = NSEngine::NSActor::CCreepTankRecord(id);

						creep_tank->UnpackRecord(packet.get(), &creep_tank_record);
						creep_tank->Deserialize(&creep_tank_record);

						break;
					}

					case NSEngine::EActorType::CREEP_BULLET: {
						auto creep_bullet = static_cast<NSClient::NSActor::pCreepBullet>(world->game_objects[id].get());
						auto creep_bullet_record = NSEngine::NSActor::CCreepBulletRecord(id);

						creep_bullet->UnpackRecord(packet.get(), &creep_bullet_record);
						creep_bullet->Deserialize(&creep_bullet_record);

						break;
					}

					case NSEngine::EActorType::TURRET: {
						auto turret = static_cast<NSClient::NSActor::pTurret>(world->game_objects[id].get());
						auto turret_record = NSEngine::NSActor::CTurretRecord(id);

						turret->UnpackRecord(packet.get(), &turret_record);
						turret->Deserialize(&turret_record);

						break;
					}

					case NSEngine::EActorType::TURRET_BULLET: {
						auto turret_bullet = static_cast<NSClient::NSActor::pTurretBullet>(world->game_objects[id].get());
						auto turret_bullet_record = NSEngine::NSActor::CTurretBulletRecord(id);

						turret_bullet->UnpackRecord(packet.get(), &turret_bullet_record);
						turret_bullet->Deserialize(&turret_bullet_record);

						break;
					}

					case NSEngine::EActorType::HEADQUARTER: {
						auto headquarter = static_cast<NSClient::NSActor::pHeadquarter>(world->game_objects[id].get());
						auto headquarter_record = NSEngine::NSActor::CHeadquarterRecord(id);

						headquarter->UnpackRecord(packet.get(), &headquarter_record);
						headquarter->Deserialize(&headquarter_record);

						break;
					}

					case NSEngine::EActorType::FACTORY: {
						auto factory = static_cast<NSClient::NSActor::pFactory>(world->game_objects[id].get());
						auto factory_record = NSEngine::NSActor::CFactoryRecord(id);

						factory->UnpackRecord(packet.get(), &factory_record);
						factory->Deserialize(&factory_record);

						break;
					}

					case NSEngine::EActorType::REPAIR_KIT: {
						auto repair_kit = static_cast<NSClient::NSActor::pRepairKit>(world->game_objects[id].get());
						auto repair_kit_record = NSEngine::NSActor::CRepairKitRecord(id);

						repair_kit->UnpackRecord(packet.get(), &repair_kit_record);
						repair_kit->Deserialize(&repair_kit_record);

						break;
					}

					case NSEngine::EActorType::POWER_UP: {
						auto power_up = static_cast<NSClient::NSActor::pPowerUp>(world->game_objects[id].get());
						auto power_up_record = NSEngine::NSActor::CPowerUpRecord(id);

						power_up->UnpackRecord(packet.get(), &power_up_record);
						power_up->Deserialize(&power_up_record);

						break;
					}

					case NSEngine::EActorType::WALL: {
						auto wall = static_cast<NSClient::NSActor::pWall>(world->game_objects[id].get());
						auto wall_record = NSEngine::NSActor::CWallRecord(id);

						wall->UnpackRecord(packet.get(), &wall_record);
						wall->Deserialize(&wall_record);

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