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
		for (auto& game_object : game_objects) {
			game_object.second->Update(elapsed);
		}

		physics_world->Step(elapsed, 8, 3);
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

void World::OnConnect() {

}

void World::OnDisconnect() {

}

void World::OnConnectFail() {

}

bool World::ProcessPacket(std::shared_ptr<Packet> packet) {
	switch (packet->GetPacketType()) {
	case PacketType::ServerLoad: {
		uint32_t game_object_count = 0;
		*packet >> game_object_count;

		for (uint32_t i = 0; i < game_object_count; i++) {
			uint32_t type = 0;
			uint32_t id = 0;
			float position_x = 0.0f;
			float position_y = 0.0f;
			float velocity_x = 0.0f;
			float velocity_y = 0.0f;

			*packet
				>> type >> id
				>> position_x >> position_y
				>> velocity_x >> velocity_y;

			switch (type) {
			case ACTOR_TYPE_TANK: {
				uint32_t player_id = 0;
				*packet >> player_id;

				pGameObject game_object = CreateGameObject(type, position_x, position_y, velocity_x, velocity_y);
				static_cast<pTank>(game_object)->player_id = player_id;
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

	default: {
		return false;
	}

	}
}

void World::SendLoadPacket() {
	auto client_load_packet = std::make_shared<Packet>(PacketType::ClientLoad);
	game->Send(client_load_packet);
}

