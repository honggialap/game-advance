#include "world.h"
#include "game.h"
#include "tank.h"
#include "bullet.h"
#include "wall.h"

pGameObject World::CreateGameObject(
	uint32_t game_object_type,
	float position_x,
	float position_y
) {
	pGameObject game_object = nullptr;
	switch (game_object_type) {
	case ACTOR_TYPE_TANK: {
		pTank game_object = new Tank(game, this, game_object_id, game_object_type);
		game_objects[game_object_id++].reset(game_object);
		game_object->Load("");
		game_object->SetPosition(position_x, position_y);
		return game_object;
	}

	case ACTOR_TYPE_BULLET: {
		pBullet game_object = new Bullet(game, this, game_object_id, game_object_type);
		game_objects[game_object_id++].reset(game_object);
		game_object->Load("");
		game_object->SetPosition(position_x, position_y);
		return game_object;
	}

	case ACTOR_TYPE_WALL: {
		pWall game_object = new Wall(game, this, game_object_id, game_object_type);
		game_objects[game_object_id++].reset(game_object);
		game_object->Load("");
		game_object->SetPosition(position_x, position_y);
		return game_object;
	}

	default:
		return game_object;
	}
}

void World::Load(std::string data_path) {
	std::ifstream data_file(data_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	gravity = b2Vec2(0, 0);
	physics_world = new b2World(gravity);
	physics_world->SetContactListener(this);

	camera.reset(sf::FloatRect(0, 0, 800, 600));
	camera.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	auto player1_tank = static_cast<pTank>(CreateGameObject(ACTOR_TYPE_TANK, 100.0f, 100.0f));
	player1_tank->SetPlayerId(uint32_t(1));

	auto player2_tank = static_cast<pTank>(CreateGameObject(ACTOR_TYPE_TANK, 200.0f, 200.0f));
	player2_tank->SetPlayerId(uint32_t(2));

	auto player3_tank = static_cast<pTank>(CreateGameObject(ACTOR_TYPE_TANK, 300.0f, 300.0f));
	player3_tank->SetPlayerId(uint32_t(3));

	auto player4_tank = static_cast<pTank>(CreateGameObject(ACTOR_TYPE_TANK, 400.0f, 400.0f));
	player4_tank->SetPlayerId(uint32_t(4));

	SendLoadPacket();
}

void World::Unload() {

	for (auto& game_object : game_objects) {
		game_object.second->Unload();
		game_object.second.reset();
	}

	game_objects.clear();

	if (physics_world != nullptr) {
		delete physics_world;
		physics_world = nullptr;
	}
}

void World::Update(float elapsed) {
	switch (state) {
	case World::Loading:
		break;

	case World::Run:
		// have not take in tick, this is incomplete, but i want to make it run first.
		while (!commands.empty()) {
			auto command = commands.front();
			switch (command->type) {

			case Command::Type::Move: {
				auto move_command = static_cast<pMoveCommand>(command);
				auto tank = static_cast<pTank>(game_objects[move_command->id].get());
				tank->SetMovement(move_command->x, move_command->y);
				break;
			}

			}

			commands.pop_front();
		}

		for (auto& game_object : game_objects) {
			game_object.second->Update(elapsed);
		}

		physics_world->Step(elapsed, 8, 3);

		SendGameStatePacket();
		break;
	}
}

void World::Render(sf::RenderWindow& window) {
	window.setView(camera);
	for (auto& game_object : game_objects) {
		game_object.second->Render(window);
	}
}

sf::View& World::GetCamera() {
	return camera;
}

b2World* World::GetPhysics() {
	return physics_world;
}

void World::BeginContact(b2Contact* contact) {
	auto dataA = (void*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	auto dataB = (void*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
	if (dataA && dataB) {
		auto objectA = static_cast<pGameObject>(dataA);
		auto objectB = static_cast<pGameObject>(dataB);
		objectA->OnCollisionEnter(objectB);
		objectB->OnCollisionEnter(objectA);
	}
}

void World::EndContact(b2Contact* contact) {
	auto dataA = (void*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	auto dataB = (void*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
	if (dataA && dataB) {
		auto objectA = static_cast<pGameObject>(dataA);
		auto objectB = static_cast<pGameObject>(dataB);
		objectA->OnCollisionExit(objectB);
		objectB->OnCollisionExit(objectA);
	}
}

void World::OnConnect(uint32_t connection_id) {

}

void World::OnDisconnect(uint32_t connection_id) {

}

bool World::ProcessPacket(std::shared_ptr<Packet> packet) {
	switch (packet->GetPacketType()) {
	case PacketType::ClientLoad: {
		load_client_count += 1;
		if (load_client_count == game->open_slots) {
			state = State::Run;
			SendStartGamePacket();
		}
		return true;
	}

	case PacketType::PlayerMove: {
		uint32_t client_id;
		uint32_t player_id;
		uint32_t tick;
		uint32_t command_type;
		uint32_t game_object_id;
		int32_t x;
		int32_t y;
		
		*packet
			>> client_id >> player_id
			>> tick >> command_type >> game_object_id
			>> x >> y;

		auto move_command = new MoveCommand(tick, game_object_id, x, y);
		commands.push_back(move_command);

		auto move_command_packet = std::make_shared<Packet>(PacketType::PlayerMove);
		*move_command_packet 
			<< tick << command_type << game_object_id 
			<< x << y;

		game->SendAllExcept(client_id, move_command_packet);

		return true;
	}

	default: {
		return false;
	}

	}
}

void World::SendLoadPacket() {
	auto server_load_packet = std::make_shared<Packet>(PacketType::ServerLoad);
	
	uint32_t game_objects_count = game_objects.size();
	*server_load_packet << game_objects_count;

	for (auto& element : game_objects) {
		pGameObject game_object = element.second.get();
		uint32_t type = game_object->GetType();
		uint32_t id = game_object->GetId();

		float position_x, position_y;
		game_object->GetPosition(position_x, position_y);

		float velocity_x, velocity_y;
		game_object->GetVelocity(velocity_x, velocity_y);

		*server_load_packet 
			<< type << id 
			<< position_x << position_y 
			<< velocity_x << velocity_y;

		switch (type) {

		case ACTOR_TYPE_TANK: {
			pTank tank = static_cast<pTank>(game_object);
			uint32_t player_id = tank->GetPlayerId();
			*server_load_packet << player_id;
			break;
		}

		}
	}

	game->SendAll(server_load_packet);
}

void World::SendStartGamePacket() {
	auto start_game_packet = std::make_shared<Packet>(PacketType::StartGame);
	game->SendAll(start_game_packet);
}

void World::SendGameStatePacket() {
	auto game_state = std::make_shared<Packet>(PacketType::ServerGameState);

	uint32_t game_objects_count = game_objects.size();
	*game_state << game_objects_count;

	for (auto& element : game_objects) {
		pGameObject game_object = element.second.get();
		uint32_t type = game_object->GetType();
		uint32_t id = game_object->GetId();

		float position_x, position_y;
		game_object->GetPosition(position_x, position_y);

		float velocity_x, velocity_y;
		game_object->GetVelocity(velocity_x, velocity_y);

		*game_state
			<< type << id
			<< position_x << position_y
			<< velocity_x << velocity_y;

		switch (type) {

		case ACTOR_TYPE_TANK: {
			pTank tank = static_cast<pTank>(game_object);
			uint32_t player_id = tank->GetPlayerId();
			*game_state << player_id;
			break;
		}

		}
	}

	game->SendAll(game_state);
}
