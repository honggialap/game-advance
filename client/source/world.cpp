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

	gravity = b2Vec2(0, 0);
	physics_world = new b2World(gravity);
	physics_world->SetContactListener(this);

	camera.reset(sf::FloatRect(0, 0, 800, 600));
	camera.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	uint32_t game_object_id = this->game_object_id;
	this->game_object_id++;
	uint32_t game_object_type = ACTOR_TYPE_TANK;
	gameObjects[game_object_id].reset(CreateGameObject(game_object_type));
	gameObjects[game_object_id]->Load("");
	gameObjects[game_object_id]->SetId(game_object_id);
	gameObjects[game_object_id]->SetSync(false);
	pTank tank = static_cast<pTank>(gameObjects[game_object_id].get());
	tank->SetPlayerControl(true);

	auto local_player_spawn = std::make_shared<Packet>(PacketType::LocalPlayerSpawn);
	uint32_t id = game->GetId();
	*local_player_spawn << id << game_object_id << game_object_type;
	game->Send(local_player_spawn);

	Sleep(DWORD(2000));
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



	tick_count += 1;

	for (auto& game_object : gameObjects) {
		game_object.second->Update(elapsed);
	}

	physics_world->Step(elapsed, 8, 3);
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

void World::OnConnect() {

}

void World::OnDisconnect() {

}

void World::OnConnectFail() {

}

bool World::ProcessPacket(std::shared_ptr<Packet> packet) {
	switch (packet->GetPacketType()) {

	case PacketType::Sync: {
		return true;
	}


	case PacketType::LocalPlayerSpawn: {
		uint32 game_object_id;
		uint32 networks_id;
		*packet >> game_object_id >> networks_id;
		networksObjects[networks_id] = game_object_id;
		gameObjects[game_object_id]->SetNetworksId(networks_id);
		gameObjects[game_object_id]->SetSync(true);
		return true;
	}

	case PacketType::RemotePlayerSpawn: {
		uint32 game_object_id = this->game_object_id;
		uint32 networks_id;
		uint32 game_object_type;

		*packet >> networks_id >> game_object_type;
		gameObjects[game_object_id].reset(CreateGameObject(game_object_type));
		gameObjects[game_object_id]->Load("");
		networksObjects[networks_id] = game_object_id;
		gameObjects[game_object_id]->SetId(game_object_id);
		gameObjects[game_object_id]->SetNetworksId(networks_id);
		gameObjects[game_object_id]->SetSync(true);
		
		this->game_object_id++;
		return true;
	}

	case PacketType::PlayerMove: {
		uint32_t networks_id = 0;
		int32_t movement_x = 0;
		int32_t movement_y = 0;

		*packet >> networks_id >> movement_x >> movement_y;
		pTank tank = static_cast<pTank>(gameObjects[networksObjects[networks_id]].get());
		tank->SetMovement(movement_x, movement_y);
		printf("ID: %d, %d, %d \n", networks_id, movement_x, movement_y);
		return true;
	}

	default: {
		return false;
	}

	}
}