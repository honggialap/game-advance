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

	font.loadFromFile("data/resources/fonts/arial.ttf");
	text.setFont(font);

	auto player1_tank = static_cast<pTank>(CreateGameObject(ACTOR_TYPE_TANK, 100.0f, 100.0f));
	player1_tank->SetPlayerId(uint32_t(1));
	player_ping[1] = 0;

	auto player2_tank = static_cast<pTank>(CreateGameObject(ACTOR_TYPE_TANK, 200.0f, 200.0f));
	player2_tank->SetPlayerId(uint32_t(2));
	player_ping[2] = 0;

	auto player3_tank = static_cast<pTank>(CreateGameObject(ACTOR_TYPE_TANK, 300.0f, 300.0f));
	player3_tank->SetPlayerId(uint32_t(3));
	player_ping[3] = 0;

	auto player4_tank = static_cast<pTank>(CreateGameObject(ACTOR_TYPE_TANK, 400.0f, 400.0f));
	player4_tank->SetPlayerId(uint32_t(4));
	player_ping[4] = 0;

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

		std::stringstream displaying;
		for (auto& player : player_ping) {
			displaying 
				<< "Player " << player.first 
				<< " - Ping: " << player.second << '\n';
		}
		text.setString(displaying.str());

		//if (tick_per_game_state_count >= tick_per_game_state) {
		//
		//	for (uint32_t i = 0; i < 4; i++) {
		//		for (auto& game_object : game_objects) {
		//		}
		//
		//		physics_world->Step(elapsed, 8, 3);
		//	}
		//
		//	tick_per_game_state_count = 0;
		//}

		break;
	}
}

void World::Render(sf::RenderWindow& window) {
	window.setView(camera);
	window.draw(text);

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

	case PacketType::Ping: {
		uint32_t client_id = 0;
		uint32_t player_id = 0;
		uint32_t reply_tick = 0;
		uint32_t ping = 0;

		*packet
			>> client_id
			>> player_id
			>> reply_tick
			>> ping
			;

		player_ping[player_id] = ping;

		auto ping_reply_packet = std::make_shared<Packet>(PacketType::Ping);
		*ping_reply_packet << reply_tick;
		game->Send(client_id, ping_reply_packet);

		return true;
	}

	case PacketType::PlayerMove: {
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
	//auto game_state = std::make_shared<Packet>(PacketType::ServerGameState);
	//
	//uint32_t tick = server_tick;
	//*game_state << tick;
	//
	//uint32_t player_count = ack_tick.size();
	//*game_state << player_count;
	//for (auto& client : ack_tick) {
	//	*game_state << client.first << client.second;
	//}
	//
	//uint32_t game_objects_count = game_objects.size();
	//*game_state << game_objects_count;
	//
	//for (auto& element : game_objects) {
	//	pGameObject game_object = element.second.get();
	//	uint32_t type = game_object->GetType();
	//	uint32_t id = game_object->GetId();
	//
	//	float position_x, position_y;
	//	game_object->GetPosition(position_x, position_y);
	//
	//	float velocity_x, velocity_y;
	//	game_object->GetVelocity(velocity_x, velocity_y);
	//
	//	*game_state
	//		<< type << id
	//		<< position_x << position_y
	//		<< velocity_x << velocity_y;
	//
	//	switch (type) {
	//
	//	case ACTOR_TYPE_TANK: {
	//		pTank tank = static_cast<pTank>(game_object);
	//		uint32_t player_id = tank->GetPlayerId();
	//		*game_state << player_id;
	//		break;
	//	}
	//
	//	}
	//}
	//
	//game->SendAll(game_state);
}

void World::RelayMoveCommand(uint32_t sent_client_id, pMoveCommand move_command) {
	//auto move_command_packet = std::make_shared<Packet>(PacketType::PlayerMove);
	//
	//game->SendAllExcept(sent_client_id, move_command_packet);
}

void World::SerializeGameState() {
	//auto game_state = new GameState();
	//game_state->tick = server_tick;
	//
	//for (auto& game_object : game_objects) {
	//	game_state->game_objects_state[game_object.first] = game_object.second->Serialize();
	//}
	//
	//game_states.push_back(game_state);
}

void World::DeserializeGameState() {

}
