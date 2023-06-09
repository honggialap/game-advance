#include "server/core/main_scene.h"
#include "server/core/game.h"

#include "server/actor/game_master.h"
#include "server/actor/player_tank.h"
#include "server/actor/player_bullet.h"
#include "server/actor/creep_tank.h"
#include "server/actor/creep_bullet.h"
#include "server/actor/turret.h"
#include "server/actor/turret_bullet.h"
#include "server/actor/headquarter.h"
#include "server/actor/factory.h"
#include "server/actor/repair_kit.h"
#include "server/actor/power_up.h"
#include "server/actor/bound.h"
#include "server/actor/wall.h"
#include "server/actor/tree.h"
#include "server/actor/water.h"

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

			font.loadFromFile("data/resources/fonts/arial.ttf");
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
				if (world->rollback) {
					uint32_t last_tick = world->latest_tick - 1;
					uint32_t deserialize_tick = world->rollback_tick - 1;

					world->TrimRecords(deserialize_tick, last_tick);
					world->Deserialize(deserialize_tick);

					for (uint32_t rollback_tick = world->rollback_tick;
						rollback_tick <= last_tick;
						rollback_tick++) {

						world->Step(rollback_tick, elapsed);
						world->Serialize(rollback_tick);
					}

					world->rollback = false;
					world->rollback_tick = last_tick;
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
				for (auto& game_object_container : world->game_objects) {
					auto game_object = game_object_container.second.get();
					if (dynamic_cast<NSEngine::NSComponent::pRenderable>(game_object)) {
						dynamic_cast<NSEngine::NSComponent::pRenderable>(game_object)->Render(window);
					}
				}
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
					world->rollback = true;
					if (world->rollback_tick > tick) {
						world->rollback_tick = tick;
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

				switch (type) {

				case NSEngine::EActorType::GAME_MASTER: {
					NSServer::NSActor::pGameMaster game_master = static_cast<NSServer::NSActor::pGameMaster>(game_object);

					break;
				}

				case NSEngine::EActorType::PLAYER_TANK: {
					NSServer::NSActor::pPlayerTank player_tank = static_cast<NSServer::NSActor::pPlayerTank>(game_object);

					uint32_t player_id = player_tank->GetPlayerId();
					*server_load_packet << player_id;

					uint32_t team = player_tank->GetTeam();
					*server_load_packet << team;

					break;
				}

				case NSEngine::EActorType::PLAYER_BULLET: {
					NSServer::NSActor::pPlayerBullet player_bullet = static_cast<NSServer::NSActor::pPlayerBullet>(game_object);

					uint32_t team = player_bullet->GetTeam();
					*server_load_packet << team;

					break;
				}

				case NSEngine::EActorType::CREEP_TANK: {
					NSServer::NSActor::pCreepTank creep_tank = static_cast<NSServer::NSActor::pCreepTank>(game_object);

					uint32_t team = creep_tank->GetTeam();
					*server_load_packet << team;

					break;
				}

				case NSEngine::EActorType::CREEP_BULLET: {
					NSServer::NSActor::pCreepBullet creep_bullet = static_cast<NSServer::NSActor::pCreepBullet>(game_object);

					uint32_t team = creep_bullet->GetTeam();
					*server_load_packet << team;

					break;
				}

				case NSEngine::EActorType::TURRET: {
					NSServer::NSActor::pTurret turret = static_cast<NSServer::NSActor::pTurret>(game_object);

					uint32_t team = turret->GetTeam();
					*server_load_packet << team;

					break;
				}

				case NSEngine::EActorType::TURRET_BULLET: {
					NSServer::NSActor::pTurretBullet turret_bullet = static_cast<NSServer::NSActor::pTurretBullet>(game_object);

					uint32_t team = turret_bullet->GetTeam();
					*server_load_packet << team;

					break;
				}

				case NSEngine::EActorType::HEADQUARTER: {
					NSServer::NSActor::pHeadquarter head_quarter = static_cast<NSServer::NSActor::pHeadquarter>(game_object);

					uint32_t team = head_quarter->GetTeam();
					*server_load_packet << team;

					break;
				}

				case NSEngine::EActorType::FACTORY: {
					NSServer::NSActor::pFactory factory = static_cast<NSServer::NSActor::pFactory>(game_object);

					uint32_t team = factory->GetTeam();
					*server_load_packet << team;

					break;
				}

				case NSEngine::EActorType::REPAIR_KIT: {
					NSServer::NSActor::pRepairKit repair_kit = static_cast<NSServer::NSActor::pRepairKit>(game_object);

					break;
				}

				case NSEngine::EActorType::POWER_UP: {
					NSServer::NSActor::pPowerUp power_up = static_cast<NSServer::NSActor::pPowerUp>(game_object);

					break;
				}

				case NSEngine::EActorType::BOUND: {
					NSServer::NSActor::pBound bound = static_cast<NSServer::NSActor::pBound>(game_object);

					break;
				}

				case NSEngine::EActorType::WALL: {
					NSServer::NSActor::pWall wall = static_cast<NSServer::NSActor::pWall>(game_object);

					break;
				}

				case NSEngine::EActorType::TREE: {
					NSServer::NSActor::pTree tree = static_cast<NSServer::NSActor::pTree>(game_object);

					break;
				}

				case NSEngine::EActorType::WATER: {
					NSServer::NSActor::pWater water = static_cast<NSServer::NSActor::pWater>(game_object);

					break;
				}

				}

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

				switch (NSEngine::EActorType(type)) {
				case NSEngine::EActorType::GAME_MASTER: {
					NSEngine::NSActor::pGameMasterRecord game_master_record = static_cast<NSEngine::NSActor::pGameMasterRecord>(record.get());
					break;
				}

				case NSEngine::EActorType::PLAYER_TANK: {
					NSEngine::NSActor::pPlayerTankRecord player_tank_record = static_cast<NSEngine::NSActor::pPlayerTankRecord>(record.get());

					float position_x = player_tank_record->position_x;
					float position_y = player_tank_record->position_y;
					*game_state_packet << position_x << position_y;

					float velocity_x = player_tank_record->velocity_x;
					float velocity_y = player_tank_record->velocity_y;
					*game_state_packet << velocity_x << velocity_y;

					int32_t movement_x = player_tank_record->movement_x;
					int32_t movement_y = player_tank_record->movement_y;
					*game_state_packet << movement_x << movement_y;

					break;
				}

				case NSEngine::EActorType::PLAYER_BULLET: {
					NSEngine::NSActor::pPlayerBulletRecord player_bullet_record = static_cast<NSEngine::NSActor::pPlayerBulletRecord>(record.get());

					float position_x = player_bullet_record->position_x;
					float position_y = player_bullet_record->position_y;
					*game_state_packet << position_x << position_y;

					float velocity_x = player_bullet_record->velocity_x;
					float velocity_y = player_bullet_record->velocity_y;
					*game_state_packet << velocity_x << velocity_y;

					break;
				}

				case NSEngine::EActorType::CREEP_TANK: {
					NSEngine::NSActor::pCreepTankRecord creep_tank_record = static_cast<NSEngine::NSActor::pCreepTankRecord>(record.get());

					float position_x = creep_tank_record->position_x;
					float position_y = creep_tank_record->position_y;
					*game_state_packet << position_x << position_y;

					float velocity_x = creep_tank_record->velocity_x;
					float velocity_y = creep_tank_record->velocity_y;
					*game_state_packet << velocity_x << velocity_y;

					break;
				}

				case NSEngine::EActorType::CREEP_BULLET: {
					NSEngine::NSActor::pCreepBulletRecord creep_bullet_record = static_cast<NSEngine::NSActor::pCreepBulletRecord>(record.get());

					float position_x = creep_bullet_record->position_x;
					float position_y = creep_bullet_record->position_y;
					*game_state_packet << position_x << position_y;

					float velocity_x = creep_bullet_record->velocity_x;
					float velocity_y = creep_bullet_record->velocity_y;
					*game_state_packet << velocity_x << velocity_y;

					break;
				}

				case NSEngine::EActorType::TURRET: {
					NSEngine::NSActor::pTurretRecord turret_record = static_cast<NSEngine::NSActor::pTurretRecord>(record.get());

					break;
				}

				case NSEngine::EActorType::TURRET_BULLET: {
					NSEngine::NSActor::pTurretBulletRecord turret_bullet_record = static_cast<NSEngine::NSActor::pTurretBulletRecord>(record.get());

					float position_x = turret_bullet_record->position_x;
					float position_y = turret_bullet_record->position_y;
					*game_state_packet << position_x << position_y;

					float velocity_x = turret_bullet_record->velocity_x;
					float velocity_y = turret_bullet_record->velocity_y;
					*game_state_packet << velocity_x << velocity_y;
					break;
				}

				case NSEngine::EActorType::HEADQUARTER: {
					NSEngine::NSActor::pHeadquarterRecord headquarter_record = static_cast<NSEngine::NSActor::pHeadquarterRecord>(record.get());

					break;
				}

				case NSEngine::EActorType::FACTORY: {
					NSEngine::NSActor::pFactoryRecord factory_record = static_cast<NSEngine::NSActor::pFactoryRecord>(record.get());

					break;
				}

				case NSEngine::EActorType::REPAIR_KIT: {
					NSEngine::NSActor::pRepairKitRecord repair_kit_record = static_cast<NSEngine::NSActor::pRepairKitRecord>(record.get());

					float position_x = repair_kit_record->position_x;
					float position_y = repair_kit_record->position_y;
					*game_state_packet << position_x << position_y;

					break;
				}

				case NSEngine::EActorType::POWER_UP: {
					NSEngine::NSActor::pPowerUpRecord power_up_record = static_cast<NSEngine::NSActor::pPowerUpRecord>(record.get());

					float position_x = power_up_record->position_x;
					float position_y = power_up_record->position_y;
					*game_state_packet << position_x << position_y;

					break;
				}

				case NSEngine::EActorType::WALL: {
					NSEngine::NSActor::pWallRecord wall_record = static_cast<NSEngine::NSActor::pWallRecord>(record.get());

					break;
				}

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
