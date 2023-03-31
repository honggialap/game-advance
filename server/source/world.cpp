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

	tank.reset(CreateGameObject(ACTOR_TYPE_TANK));
	tank->Load("");

	bullet.reset(CreateGameObject(ACTOR_TYPE_BULLET));
	bullet->Load("");

	wall.reset(CreateGameObject(ACTOR_TYPE_WALL));
	wall->Load("");
}

void World::Unload() {
	tank->Unload();
	tank.reset();

	bullet->Unload();
	bullet.reset();

	wall->Unload();
	wall.reset();

	if (physics_world != nullptr) {
		delete physics_world;
		physics_world = nullptr;
	}
}

void World::Update(float elapsed) {
	tank->Update(elapsed);
	bullet->Update(elapsed);
	wall->Update(elapsed);
}

void World::Render(sf::RenderWindow& window) {
	window.setView(camera);
	tank->Render(window);
	bullet->Render(window);
	wall->Render(window);
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
	return true;
}