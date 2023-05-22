#include "main_scene.h"
#include "game_client.h"

#include "game_master.h"
#include "player_tank.h"
#include "player_bullet.h"
#include "creep_tank.h"
#include "creep_bullet.h"
#include "turret.h"
#include "turret_bullet.h"
#include "headquarter.h"
#include "factory.h"
#include "repair_kit.h"
#include "power_up.h"
#include "bound.h"
#include "wall.h"
#include "tree.h"
#include "water.h"

MainScene::MainScene(pGame game) 
	: ClientScene(game) 
{}

MainScene::~MainScene() {}

void MainScene::Load(std::string data_path) {
	std::ifstream data_file(data_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	float window_width = (float)game->GetWindow().getSize().x;
	float window_height = (float)game->GetWindow().getSize().y;
	camera.reset(sf::FloatRect(0, 0, window_width, window_height));
	camera.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	font.loadFromFile("data/resources/fonts/arial.ttf");
	text.setFont(font);

	world = new ClientWorld(game);
}

void MainScene::Unload() {
	if (world) {
		world->game_objects.clear();
		delete world;
		world = nullptr;
	}
}

void MainScene::Update(float elapsed) {
	switch (state) {
	case MainScene::Loading:
		if (!ready_sent) {
			SendReadyPacket();
			ready_sent = true;
		}
		break;

	case MainScene::Run: {
		if (world->just_got_game_state) {
			world->just_got_game_state = false;
			for (uint32_t reconcilate_tick = world->server_tick + 1;
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

void MainScene::Render(sf::RenderWindow& window) {
	window.setView(camera);
	window.draw(text);

	switch (state) {
	case MainScene::Loading: {
		break;
	}

	case MainScene::Run: {
		for (auto& game_object_container : world->game_objects) {
			game_object_container.second->Render(window);
		}
		break;
	}
	}

}

sf::View& MainScene::GetCamera() {
	return camera;
}

void MainScene::OnConnect() {

}

void MainScene::OnDisconnect() {

}

void MainScene::OnConnectFail() {

}

bool MainScene::ProcessPacket(std::shared_ptr<Packet> packet) {
	switch (packet->GetPacketType()) {

	case PacketType::ServerLoad: {
		uint32_t game_object_count = 0;
		*packet >> game_object_count;

		for (uint32_t i = 0; i < game_object_count; i++) {
			uint32_t type;
			*packet >> type;
			switch (type) {

			case ACTOR_GAME_MASTER: {
				std::string name;
				*packet >> name;

				float position_x, position_y;
				*packet >> position_x >> position_y;

				uint32_t layer;
				*packet >> layer;
				
				std::string data_path;
				*packet >> data_path;

				auto game_master = GameMaster::Create(game, world, name, position_x, position_y, layer, data_path);
				break;
			}

			case ACTOR_PLAYER_TANK: {
				std::string name;
				*packet >> name;
				
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

				auto tank = PlayerTank::Create(game, world, name, position_x, position_y, layer, data_path);
				tank->SetPlayerId(player_id);
				if (tank->GetPlayerId() == game_client->GetPlayerId()) {
					tank->SetPlayerControl(true);
				}
				break;
			}

			case ACTOR_PLAYER_BULLET: {
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

				auto player_bullet = PlayerBullet::Create(game, world, name, position_x, position_y, layer, data_path);
				break;
			}

			case ACTOR_CREEP_TANK: {
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

				auto creep_tank = CreepTank::Create(game, world, name, position_x, position_y, layer, data_path);
				break;
			}

			case ACTOR_CREEP_BULLET: {
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

				auto creep_bullet = CreepBullet::Create(game, world, name, position_x, position_y, layer, data_path);
				break;
			}

			case ACTOR_TURRET: {
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

				auto turret = Turret::Create(game, world, name, position_x, position_y, layer, data_path);
				break;
			}

			case ACTOR_TURRET_BULLET: {
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

				auto turret_bullet = TurretBullet::Create(game, world, name, position_x, position_y, layer, data_path);
				break;
			}

			case ACTOR_HEADQUARTER: {
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

				auto headquarter = Headquarter::Create(game, world, name, position_x, position_y, layer, data_path);
				break;
			}

			case ACTOR_FACTORY: {
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

				auto factory = Factory::Create(game, world, name, position_x, position_y, layer, data_path);
				break;
			}

			case ACTOR_REPAIR_KIT: {
				std::string name;
				*packet >> name;

				float position_x, position_y;
				*packet >> position_x >> position_y;

				uint32_t layer;
				*packet >> layer;

				std::string data_path;
				*packet >> data_path;

				auto repair_kit = RepairKit::Create(game, world, name, position_x, position_y, layer, data_path);
				break;
			}

			case ACTOR_POWER_UP: {
				std::string name;
				*packet >> name;

				float position_x, position_y;
				*packet >> position_x >> position_y;

				uint32_t layer;
				*packet >> layer;

				std::string data_path;
				*packet >> data_path;

				auto power_up = PowerUp::Create(game, world, name, position_x, position_y, layer, data_path);
				break;
			}

			case ACTOR_BOUND: {
				std::string name;
				*packet >> name;

				float position_x, position_y;
				*packet >> position_x >> position_y;

				uint32_t layer;
				*packet >> layer;

				std::string data_path;
				*packet >> data_path;

				auto bound = Bound::Create(game, world, name, position_x, position_y, layer, data_path);
				break;
			}

			case ACTOR_WALL: {
				std::string name;
				*packet >> name;

				float position_x, position_y;
				*packet >> position_x >> position_y;

				uint32_t layer;
				*packet >> layer;

				std::string data_path;
				*packet >> data_path;

				auto wall = Wall::Create(game, world, name, position_x, position_y, layer, data_path);
				break;
			}

			case ACTOR_TREE: {
				std::string name;
				*packet >> name;

				float position_x, position_y;
				*packet >> position_x >> position_y;

				uint32_t layer;
				*packet >> layer;

				std::string data_path;
				*packet >> data_path;

				auto tree = Tree::Create(game, world, name, position_x, position_y, layer, data_path);
				break;
			}

			case ACTOR_WATER: {
				std::string name;
				*packet >> name;

				float position_x, position_y;
				*packet >> position_x >> position_y;

				uint32_t layer;
				*packet >> layer;

				std::string data_path;
				*packet >> data_path;

				auto water = Water::Create(game, world, name, position_x, position_y, layer, data_path);
				break;
			}

			}
		}

		SendLoadPacket();

		return true;
	}

	case PacketType::StartGame: {
		state = State::Run;
		return true;
	}

	case PacketType::Ping: {
		uint32_t reply_ping_tick;
		*packet >> reply_ping_tick;
		ping_tick = (world->latest_tick - reply_ping_tick) / 2;
		ping_sent = false;
		return true;
	}

	case PacketType::ServerGameState: {
		world->just_got_game_state = true;

		uint32_t server_tick = 0;
		*packet >> server_tick;
		world->server_tick = server_tick;

		uint32_t game_object_count = 0;
		*packet >> game_object_count;
		for (uint32_t i = 0; i < game_object_count; i++) {
			uint32_t type = 0;
			*packet >> type;

			uint32_t id = 0;
			*packet >> id;

			switch (type) {
			case ACTOR_GAME_MASTER: {
				GameMaster* game_master = static_cast<GameMaster*>(world->game_objects[id].get());

				break;
			}

			case ACTOR_PLAYER_TANK: {
				float position_x, position_y;
				*packet >> position_x >> position_y;

				float velocity_x, velocity_y;
				*packet >> velocity_x >> velocity_y;

				int32_t movement_x, movement_y;
				*packet >> movement_x >> movement_y;

				PlayerTank* player_tank = static_cast<PlayerTank*>(world->game_objects[id].get());
				player_tank->last_known_x = player_tank->latest_x;
				player_tank->last_known_y = player_tank->latest_y;
				player_tank->latest_x = position_x;
				player_tank->latest_y = position_y;

				player_tank->SetPosition(position_x, position_y);
				player_tank->SetVelocity(velocity_x, velocity_y);
				player_tank->SetMovement(movement_x, movement_y);

				break;
			}

			case ACTOR_PLAYER_BULLET: {
				float position_x, position_y;
				*packet >> position_x >> position_y;

				float velocity_x, velocity_y;
				*packet >> velocity_x >> velocity_y;

				PlayerBullet* player_bullet = static_cast<PlayerBullet*>(world->game_objects[id].get());
				player_bullet->SetPosition(position_x, position_y);
				player_bullet->SetVelocity(velocity_x, velocity_y);

				break;
			}

			case ACTOR_CREEP_TANK: {
				float position_x, position_y;
				*packet >> position_x >> position_y;

				float velocity_x, velocity_y;
				*packet >> velocity_x >> velocity_y;

				CreepTank* creep_tank = static_cast<CreepTank*>(world->game_objects[id].get());
				creep_tank->SetPosition(position_x, position_y);
				creep_tank->SetVelocity(velocity_x, velocity_y);

				break;
			}

			case ACTOR_CREEP_BULLET: {
				float position_x, position_y;
				*packet >> position_x >> position_y;

				float velocity_x, velocity_y;
				*packet >> velocity_x >> velocity_y;

				CreepBullet* creep_bullet = static_cast<CreepBullet*>(world->game_objects[id].get());
				creep_bullet->SetPosition(position_x, position_y);
				creep_bullet->SetVelocity(velocity_x, velocity_y);

				break;
			}

			case ACTOR_TURRET: {
				Turret* turret = static_cast<Turret*>(world->game_objects[id].get());

				break;
			}

			case ACTOR_TURRET_BULLET: {
				float position_x, position_y;
				*packet >> position_x >> position_y;

				float velocity_x, velocity_y;
				*packet >> velocity_x >> velocity_y;

				TurretBullet* turret_bullet = static_cast<TurretBullet*>(world->game_objects[id].get());
				turret_bullet->SetPosition(position_x, position_y);
				turret_bullet->SetVelocity(velocity_x, velocity_y);

				break;
			}

			case ACTOR_HEADQUARTER: {
				Headquarter* headquarter = static_cast<Headquarter*>(world->game_objects[id].get());

				break;
			}

			case ACTOR_FACTORY: {
				Factory* factory = static_cast<Factory*>(world->game_objects[id].get());

				break;
			}

			case ACTOR_REPAIR_KIT: {
				float position_x, position_y;
				*packet >> position_x >> position_y;

				RepairKit* repair_kit = static_cast<RepairKit*>(world->game_objects[id].get());
				repair_kit->SetPosition(position_x, position_y);

				break;
			}

			case ACTOR_POWER_UP: {
				float position_x, position_y;
				*packet >> position_x >> position_y;

				PowerUp* power_up = static_cast<PowerUp*>(world->game_objects[id].get());
				power_up->SetPosition(position_x, position_y);

				break;
			}

			case ACTOR_BOUND: {
				Bound* bound = static_cast<Bound*>(world->game_objects[id].get());

				break;
			}

			case ACTOR_WALL: {
				Wall* wall = static_cast<Wall*>(world->game_objects[id].get());

				break;
			}

			case ACTOR_TREE: {
				Tree* tree = static_cast<Tree*>(world->game_objects[id].get());

				break;
			}
			
			case ACTOR_WATER: {
				Water* water = static_cast<Water*>(world->game_objects[id].get());

				break;
			}

			}
		}
		return true;
	}

	case PacketType::PlayerMove: {
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

		MoveCommand move_command(game_object_id, x, y);
		world->commands[tick].push_back(
			std::make_unique<MoveCommand>(move_command)
		);

		return true;
	}

	default: {
		return false;
	}

	}
}

void MainScene::SendReadyPacket() {
	auto ready_packet = std::make_shared<Packet>(PacketType::ClientReady);
	game_client->Send(ready_packet);
}

void MainScene::SendLoadPacket() {
	auto client_load_packet = std::make_shared<Packet>(PacketType::ClientLoad);
	game_client->Send(client_load_packet);
}

void MainScene::SendPingPacket() {
	auto ping_packet = std::make_shared<Packet>(PacketType::Ping);
	*ping_packet
		<< game_client->GetClientId()
		<< game_client->GetPlayerId()
		<< world->latest_tick
		<< ping_tick
		;
	game_client->Send(ping_packet);
	ping_sent = true;
}