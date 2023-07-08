#include "client/core/main_scene.h"
#include "client/core/game.h"

#include "client/actor/game_master.h"
#include "client/actor/headquarter.h"

#include "client/actor/tank/player_tank.h"
#include "client/actor/tank/basic_tank.h"
#include "client/actor/tank/fast_tank.h"
#include "client/actor/tank/power_tank.h"
#include "client/actor/tank/armor_tank.h"
#include "client/actor/tank/bullet.h"

#include "client/actor/power_up/grenade.h"
#include "client/actor/power_up/helmet.h"
#include "client/actor/power_up/shovel.h"
#include "client/actor/power_up/star.h"
#include "client/actor/power_up/tank.h"
#include "client/actor/power_up/timer.h"

#include "client/actor/terrain/bound.h"
#include "client/actor/terrain/brick.h"
#include "client/actor/terrain/ice.h"
#include "client/actor/terrain/steel.h"
#include "client/actor/terrain/tree.h"
#include "client/actor/terrain/water.h"

#include "client/actor/effect/explosion.h"
#include "client/actor/effect/impact.h"
#include "client/actor/effect/score.h"

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

			font.loadFromFile("data/resource/font/arial.ttf");
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

					case NSEngine::EActorType::HEADQUARTER: {
						game_object = NSClient::NSActor::CHeadquarter::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::PLAYER_TANK: {
						game_object = NSClient::NSActor::CPlayerTank::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::BASIC_TANK: {
						game_object = NSClient::NSActor::CBasicTank::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::FAST_TANK: {
						game_object = NSClient::NSActor::CFastTank::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::POWER_TANK: {
						game_object = NSClient::NSActor::CPowerTank::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::ARMOR_TANK: {
						game_object = NSClient::NSActor::CArmorTank::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::BULLET: {
						game_object = NSClient::NSActor::CBullet::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::GRENADE: {
						game_object = NSClient::NSActor::CGrenade::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::HELMET: {
						game_object = NSClient::NSActor::CHelmet::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::SHOVEL: {
						game_object = NSClient::NSActor::CShovel::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::STAR: {
						game_object = NSClient::NSActor::CStar::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::TANK: {
						game_object = NSClient::NSActor::CTank::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::TIMER: {
						game_object = NSClient::NSActor::CTimer::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::BOUND: {
						game_object = NSClient::NSActor::CBound::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::BRICK: {
						game_object = NSClient::NSActor::CBrick::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::ICE: {
						game_object = NSClient::NSActor::CIce::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::STEEL: {
						game_object = NSClient::NSActor::CSteel::Create(game, world, name);
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

					case NSEngine::EActorType::EXPLOSION: {
						game_object = NSClient::NSActor::CExplosion::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::IMPACT: {
						game_object = NSClient::NSActor::CImpact::Create(game, world, name);
						break;
					}

					case NSEngine::EActorType::SCORE: {
						game_object = NSClient::NSActor::CScore::Create(game, world, name);
						break;
					}

					}

					game_object->UnpackLoadPacket(packet.get());

					if (dynamic_cast<NSEngine::NSComponent::pRenderable>(game_object)) {
						auto renderable = dynamic_cast<NSEngine::NSComponent::pRenderable>(game_object);
						world->render_queue.emplace(renderable->GetLayer(), game_object->GetId());
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

			case NSEngine::EPacketType::PLAYER_SHOOT: {
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

				NSEngine::NSActor::CShootCommand shoot_command(game_object_id, x, y);
				world->commands[tick].push_back(
					std::make_unique<NSEngine::NSActor::CShootCommand>(shoot_command)
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