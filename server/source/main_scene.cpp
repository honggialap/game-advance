#include "main_scene.h"
#include "game.h"

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

void MainScene::Load(std::string data_path) {
	std::ifstream data_file(data_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	float window_width = (float)game->GetWindow().getSize().x;
	float window_height = (float)game->GetWindow().getSize().y;
	camera.reset(sf::FloatRect(0, 0, window_width, window_height));
	camera.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	font.loadFromFile("data/resources/fonts/arial.ttf");
	text.setFont(font);

	world = new World(game);
	world->Load(data.at("world"));

	for (uint32_t i = 1; i <= game->open_slots; i++) {
		player_ping[i] = 0;
	}
}

void MainScene::Unload() {
	if (world) {
		world->Unload();
		delete world;
		world = nullptr;
	}

	player_ping.clear();
}

void MainScene::Update(float elapsed) {
	switch (state) {
	case MainScene::Loading: {
		break;
	}

	case MainScene::Run: {
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

void MainScene::OnConnect(uint32_t connection_id) {

}

void MainScene::OnDisconnect(uint32_t connection_id) {

}

bool MainScene::ProcessPacket(std::shared_ptr<Packet> packet) {
	switch (packet->GetPacketType()) {
	case PacketType::ClientReady: {
		ready_client_count += 1;
		if (ready_client_count == game->open_slots) {
			SendLoadPacket();
		}
		return true;
	}

	case PacketType::ClientLoad: {
		load_client_count += 1;
		if (load_client_count == game->open_slots) {
			state = State::Run;
			SendStartGamePacket();
		}
		return true;
	}

	case PacketType::Ping: {
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

	case PacketType::PlayerMove: {
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
			std::make_unique<MoveCommand>(game_object_id, x, y)
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

void MainScene::SendLoadPacket() {
	auto server_load_packet = std::make_shared<Packet>(PacketType::ServerLoad);

	uint32_t game_objects_count = world->game_objects.size();
	*server_load_packet << game_objects_count;

	for (auto& game_object_container : world->game_objects) {
		GameObject* game_object = game_object_container.second.get();

		uint32_t type = game_object->GetType();
		*server_load_packet << type;

		std::string name = game_object->GetName();
		*server_load_packet << name;

		float position_x, position_y;
		game_object->GetPosition(position_x, position_y);
		*server_load_packet << position_x << position_y;

		uint32_t layer = game_object->GetLayer();
		*server_load_packet << layer;

		std::string data_path = game_object->GetResourcePath();
		*server_load_packet << data_path;

		switch (type) {

		case ACTOR_GAME_MASTER: {
			GameMaster* game_master = static_cast<GameMaster*>(game_object);

			break;
		}

		case ACTOR_PLAYER_TANK: {
			PlayerTank* player_tank = static_cast<PlayerTank*>(game_object);

			uint32_t player_id = player_tank->GetPlayerId();
			*server_load_packet << player_id;

			uint32_t team = player_tank->GetTeam();
			*server_load_packet << team;

			break;
		}

		case ACTOR_PLAYER_BULLET: {
			PlayerBullet* player_bullet = static_cast<PlayerBullet*>(game_object);

			uint32_t team = player_bullet->GetTeam();
			*server_load_packet << team;

			break;
		}

		case ACTOR_CREEP_TANK: {
			CreepTank* creep_tank = static_cast<CreepTank*>(game_object);

			uint32_t team = creep_tank->GetTeam();
			*server_load_packet << team;

			break;
		}

		case ACTOR_CREEP_BULLET: {
			CreepBullet* creep_bullet = static_cast<CreepBullet*>(game_object);

			uint32_t team = creep_bullet->GetTeam();
			*server_load_packet << team;

			break;
		}

		case ACTOR_TURRET: {
			Turret* turret = static_cast<Turret*>(game_object);

			uint32_t team = turret->GetTeam();
			*server_load_packet << team;

			break;
		}

		case ACTOR_TURRET_BULLET: {
			TurretBullet* turret_bullet = static_cast<TurretBullet*>(game_object);

			uint32_t team = turret_bullet->GetTeam();
			*server_load_packet << team;

			break;
		}

		case ACTOR_HEADQUARTER: {
			Headquarter* head_quarter = static_cast<Headquarter*>(game_object);

			uint32_t team = head_quarter->GetTeam();
			*server_load_packet << team;
			
			break;
		}

		case ACTOR_FACTORY: {
			Factory* factory = static_cast<Factory*>(game_object);

			uint32_t team = factory->GetTeam();
			*server_load_packet << team;

			break;
		}

		case ACTOR_REPAIR_KIT: {
			RepairKit* repair_kit = static_cast<RepairKit*>(game_object);

			break;
		}

		case ACTOR_POWER_UP: {
			PowerUp* power_up = static_cast<PowerUp*>(game_object);

			break;
		}

		case ACTOR_BOUND: {
			Bound* bound = static_cast<Bound*>(game_object);

			break;
		}

		case ACTOR_WALL: {
			Wall* wall = static_cast<Wall*>(game_object);

			break;
		}

		case ACTOR_TREE: {
			Tree* tree = static_cast<Tree*>(game_object);

			break;
		}

		case ACTOR_WATER: {
			Water* water = static_cast<Water*>(game_object);

			break;
		}

		}

	}

	game->SendAll(server_load_packet);
}

void MainScene::SendStartGamePacket() {
	auto start_game_packet = std::make_shared<Packet>(PacketType::StartGame);
	game->SendAll(start_game_packet);
}

void MainScene::SendGameStatePacket() {
	auto& records = world->records[world->latest_tick - world->tick_per_game_state];

	auto game_state_packet = std::make_shared<Packet>(PacketType::ServerGameState);

	uint32_t server_tick = world->latest_tick - world->tick_per_game_state;
	*game_state_packet << server_tick;

	uint32_t game_object_count = records.size();
	*game_state_packet << game_object_count;

	for (auto& record : records) {
		uint32_t type = record->game_object_type;
		*game_state_packet << type;
		
		uint32_t id = record->game_object_id;
		*game_state_packet << id;

		switch (type) {
		case ACTOR_GAME_MASTER: {
			GameMasterRecord* game_master_record = static_cast<GameMasterRecord*>(record.get());
			break;
		}

		case ACTOR_PLAYER_TANK: {
			PlayerTankRecord* player_tank_record = static_cast<PlayerTankRecord*>(record.get());

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

		case ACTOR_PLAYER_BULLET: {
			PlayerBulletRecord* player_bullet_record = static_cast<PlayerBulletRecord*>(record.get());

			float position_x = player_bullet_record->position_x;
			float position_y = player_bullet_record->position_y;
			*game_state_packet << position_x << position_y;

			float velocity_x = player_bullet_record->velocity_x;
			float velocity_y = player_bullet_record->velocity_y;
			*game_state_packet << velocity_x << velocity_y;

			break;
		}

		case ACTOR_CREEP_TANK: {
			CreepTankRecord* creep_tank_record = static_cast<CreepTankRecord*>(record.get());

			float position_x = creep_tank_record->position_x;
			float position_y = creep_tank_record->position_y;
			*game_state_packet << position_x << position_y;

			float velocity_x = creep_tank_record->velocity_x;
			float velocity_y = creep_tank_record->velocity_y;
			*game_state_packet << velocity_x << velocity_y;

			break;
		}

		case ACTOR_CREEP_BULLET: {
			CreepBulletRecord* creep_bullet_record = static_cast<CreepBulletRecord*>(record.get());

			float position_x = creep_bullet_record->position_x;
			float position_y = creep_bullet_record->position_y;
			*game_state_packet << position_x << position_y;

			float velocity_x = creep_bullet_record->velocity_x;
			float velocity_y = creep_bullet_record->velocity_y;
			*game_state_packet << velocity_x << velocity_y;

			break;
		}

		case ACTOR_TURRET: {
			TurretRecord* turret_record = static_cast<TurretRecord*>(record.get());

			break;
		}

		case ACTOR_TURRET_BULLET: {
			TurretBulletRecord* turret_bullet_record = static_cast<TurretBulletRecord*>(record.get());

			float position_x = turret_bullet_record->position_x;
			float position_y = turret_bullet_record->position_y;
			*game_state_packet << position_x << position_y;

			float velocity_x = turret_bullet_record->velocity_x;
			float velocity_y = turret_bullet_record->velocity_y;
			*game_state_packet << velocity_x << velocity_y;
			break;
		}

		case ACTOR_HEADQUARTER: {
			HeadquarterRecord* headquarter_record = static_cast<HeadquarterRecord*>(record.get());

			break;
		}

		case ACTOR_FACTORY: {
			FactoryRecord* factory_record = static_cast<FactoryRecord*>(record.get());

			break;
		}

		case ACTOR_REPAIR_KIT: {
			RepairKitRecord* repair_kit_record = static_cast<RepairKitRecord*>(record.get());

			float position_x = repair_kit_record->position_x;
			float position_y = repair_kit_record->position_y;
			*game_state_packet << position_x << position_y;

			break;
		}

		case ACTOR_POWER_UP: {
			PowerUpRecord* power_up_record = static_cast<PowerUpRecord*>(record.get());

			float position_x = power_up_record->position_x;
			float position_y = power_up_record->position_y;
			*game_state_packet << position_x << position_y;

			break;
		}

		case ACTOR_BOUND: {
			BoundRecord* bound_record = static_cast<BoundRecord*>(record.get());

			break;
		}

		case ACTOR_WALL: {
			WallRecord* wall_record = static_cast<WallRecord*>(record.get());

			break;
		}

		case ACTOR_TREE: {
			TreeRecord* tree_record = static_cast<TreeRecord*>(record.get());

			break;
		}

		case ACTOR_WATER: {
			WaterRecord* water_record = static_cast<WaterRecord*>(record.get());

			break;
		}

		}
		
	}

	game->SendAll(game_state_packet);
}

void MainScene::SendReplyPingPacket(uint32_t client_id, uint32_t reply_ping_tick) {
	auto ping_reply_packet = std::make_shared<Packet>(PacketType::Ping);
	*ping_reply_packet << reply_ping_tick;
	game->Send(client_id, ping_reply_packet);
}