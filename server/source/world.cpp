#include "world.h"
#include "game.h"
#include "tank.h"
#include "bullet.h"
#include "wall.h"

pGameObject World::CreateGameObject(
	uint32_t game_object_type,
	float position_x,
	float position_y,
	float velocity_x,
	float velocity_y
) {
	pGameObject game_object = nullptr;
	switch (game_object_type) {
	case ACTOR_TYPE_TANK: {
		game_objects[game_object_id].reset(new Tank(game, this, game_object_id, game_object_type, position_x, position_y, velocity_x, velocity_y));
		static_cast<pTank>(game_objects[game_object_id].get())->Load("");
		game_object = game_objects[game_object_id].get();
		game_object_id += 1;
		return game_object;
	}
		
	case ACTOR_TYPE_BULLET: {
		game_objects[game_object_id].reset(new Bullet(game, this, game_object_id, game_object_type, position_x, position_y, velocity_x, velocity_y));
		static_cast<pBullet>(game_objects[game_object_id].get())->Load("");
		game_object = game_objects[game_object_id].get();
		game_object_id += 1;
		return game_object;
	}

	case ACTOR_TYPE_WALL: {
		game_objects[game_object_id].reset(new Wall(game, this, game_object_id, game_object_type, position_x, position_y, velocity_x, velocity_y));
		static_cast<pWall>(game_objects[game_object_id].get())->Load("");
		game_object = game_objects[game_object_id].get();
		game_object_id += 1;
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

	auto player1_tank = CreateGameObject(ACTOR_TYPE_TANK, 100.0f, 100.0f, 0.0f, 0.0f);
	static_cast<pTank>(player1_tank)->player_id = 1;

	auto player2_tank = CreateGameObject(ACTOR_TYPE_TANK, 200.0f, 200.0f, 0.0f, 0.0f);
	static_cast<pTank>(player2_tank)->player_id = 2;

	auto player3_tank = CreateGameObject(ACTOR_TYPE_TANK, 300.0f, 300.0f, 0.0f, 0.0f);
	static_cast<pTank>(player3_tank)->player_id = 3;

	auto player4_tank = CreateGameObject(ACTOR_TYPE_TANK, 300.0f, 300.0f, 0.0f, 0.0f);
	static_cast<pTank>(player4_tank)->player_id = 4;

	Sleep(DWORD(1000));
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

	for (auto& game_object : game_objects) {
		game_object.second->Update(elapsed);
	}
	physics_world->Step(elapsed, 8, 3);

	auto game_state_packet = std::make_shared<Packet>(PacketType::ServerGameState);
	uint32_t total_game_objects = game_objects.size();
	*game_state_packet << total_game_objects;

	for (auto& game_object : game_objects) {
		auto base = game_object.second->Serialize();
		switch (base->type) {

		case ACTOR_TYPE_TANK: {
			auto derived = static_cast<pTankState>(base);
			*game_state_packet
				<< derived->type
				<< derived->id
				<< derived->position_x
				<< derived->position_y
				<< derived->velocity_x
				<< derived->velocity_y
				<< derived->player_id;
			break;
		}

		}
	}

	game->SendAll(game_state_packet);
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


	default: {
		return false;
	}

	}
}