#include "world.h"
#include "game.h"
#include "tank.h"
#include "bullet.h"
#include "wall.h"

pGameObject World::CreateGameObject(unsigned int game_object_type) {
	switch (game_object_type) {
	case ACTOR_TYPE_TANK:
		return new Tank(game, this);
		break;

	case ACTOR_TYPE_BULLET:
		return new Bullet(game, this);
		break;

	case ACTOR_TYPE_WALL:
		return new Wall(game, this);
		break;

	default:
		return nullptr;
		break;
	}
}

void World::Load(std::string data_path) {
	std::ifstream data_file(data_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	camera.reset(sf::FloatRect(0, 0, 800, 600));
	camera.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
}

void World::Unload() {

	for (auto& game_object : gameObjects) {
		game_object.second->Unload();
		game_object.second.reset();
	}

	gameObjects.clear();

	if (physics_world != nullptr) {
		delete physics_world;
		physics_world = nullptr;
	}
}

void World::Update(float elapsed) {
	total_elapsed_ms += elapsed;
	tick_count += 1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
		total_elapsed_ms += 1000.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {
		total_elapsed_ms -= 1000.0f;
	}

	printf("TICK: %d - ELAPSED: %f \n", tick_count, total_elapsed_ms);
	
	// Camera movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		camera.move(sf::Vector2f(0, -1.0f) * elapsed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		camera.move(sf::Vector2f(0, 1.0f) * elapsed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		camera.move(sf::Vector2f(-1.0f, 0) * elapsed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		camera.move(sf::Vector2f(1.0f, 0) * elapsed);
	}

	for (auto& game_object : gameObjects) {
		game_object.second->Update(elapsed);
	}
}

void World::Render(sf::RenderWindow& window) {
	window.setView(camera);
	for (auto& game_object : gameObjects) {
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

	case PacketType::Sync: {
		uint32_t client_id = 0;
		float client_elapsed = 0;
		uint32_t client_tick = 0;

		float server_elapsed = total_elapsed_ms;
		uint32_t server_tick = tick_count;

		*packet >> client_id >> client_tick >> client_elapsed;

		auto sync_packet = std::make_shared<Packet>(PacketType::Sync);
		*sync_packet << client_tick << client_elapsed << server_tick << server_elapsed;
		game->Send(client_id, sync_packet);

		return true;
	}

	case PacketType::LocalPlayerSpawn: {
		uint32_t client_id = 0;
		uint32_t game_object_id = 0;
		uint32_t game_object_type = 0;
		uint32_t networks_object_id = this->game_object_id;
		this->game_object_id++;

		*packet >> client_id >> game_object_id >> game_object_type;
		gameObjects[networks_object_id].reset(CreateGameObject(game_object_type));
		gameObjects[networks_object_id]->Load("");
		
		auto local_spawn_reply_packet = std::make_shared<Packet>(PacketType::LocalPlayerSpawn);
		*local_spawn_reply_packet << game_object_id << networks_object_id;
		game->Send(client_id, local_spawn_reply_packet);

		auto remote_spawn_reply_packet = std::make_shared<Packet>(PacketType::RemotePlayerSpawn);
		*remote_spawn_reply_packet << networks_object_id << game_object_type;
		game->SendAllExcept(client_id, remote_spawn_reply_packet);

		return true;
	}

	case PacketType::PlayerMove: {
		uint32_t client_id = 0;
		uint32_t networks_id = 0;
		int32_t movement_x = 0;
		int32_t movement_y = 0;
		
		*packet >> client_id >> networks_id >> movement_x >> movement_y;
		gameObjects[networks_id];

		auto player_move_packet = std::make_shared<Packet>(PacketType::PlayerMove);
		*player_move_packet << networks_id << movement_x << movement_y;
		game->SendAllExcept(client_id, player_move_packet);
		
		return true;
	}

	default: {
		return false;
	}

	}
}