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

				pTank tank = static_cast<pTank>(CreateGameObject(type, position_x, position_y));
				tank->SetVelocity(velocity_x, velocity_y);
				tank->SetPlayerId(player_id);
				if (tank->GetPlayerId() == game->player_id) {
					tank->SetPlayerControl(true);
				}
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

	case PacketType::ServerGameState: {
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

				pTank tank = static_cast<pTank>(game_objects[id].get());
				tank->SetPosition(position_x, position_y);
				tank->SetVelocity(velocity_x, velocity_y);
				tank->SetPlayerId(player_id);

				break;
			}
			}
		}

		return true;
	}

	case PacketType::PlayerMove: {
		uint32_t tick;
		uint32_t command_type;
		uint32_t game_object_id;
		int32_t x;
		int32_t y;

		*packet
			>> tick >> command_type >> game_object_id
			>> x >> y;

		static_cast<pTank>(game_objects[game_object_id].get())->SetMovement(x, y);
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

