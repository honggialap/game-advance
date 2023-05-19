#include "game_master.h"
#include "game.h"
#include "world.h"

GameMaster* GameMaster::Create(pGame game, pWorld world, nlohmann::json& data) {
	uint32_t id = world->game_object_id++;

	world->game_objects[id] = std::make_unique<GameMaster>();
	world->dictionary[data.at("name")] = id;

	GameMaster* game_master = static_cast<GameMaster*>(world->game_objects[id].get());

	game_master->SetGame(game);
	game_master->SetWorld(world);
	game_master->SetId(id);
	game_master->SetType(ACTOR_GAME_MASTER);
	game_master->SetName(data.at("name"));
	game_master->SetLayer(data.at("layer"));

	game_master->Load(data.at("data_path"));
	game_master->SetResourcePath(data.at("data_path"));

	game_master->SetPosition(data.at("x"), data.at("y"));

	return game_master;
}

void GameMaster::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);

	body_def.type = b2_staticBody;
	body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	body = world->GetPhysics()->CreateBody(&body_def);

	collider.SetAsBox(32.0f / 30, 32.0f / 30);

	fixture_def.shape = &collider;
	fixture_def.density = 100.0f;
	fixture_def.friction = 0.0f;

	fixture_def.filter.categoryBits = FILTER_NON_COLLIDABLE;

	fixture = body->CreateFixture(&fixture_def);
}

void GameMaster::Unload() {
	if (body != nullptr) {
		if (fixture != nullptr) {
			body->DestroyFixture(fixture);
			fixture = nullptr;
		}
		world->GetPhysics()->DestroyBody(body);
		body = nullptr;
	}
}

void GameMaster::Serialize(uint32_t tick) {
	auto& records_container = world->records[tick];
	records_container.push_back(
		std::make_unique<GameMasterRecord>(
			id, type
		)
	);
}

void GameMaster::Deserialize(Record* record) {
	auto game_master_record = static_cast<GameMasterRecord*>(record);
}

void GameMaster::HandleInput(uint32_t tick) {
}

void GameMaster::ExecuteCommand(Command* command) {
}

void GameMaster::Update(float elapsed) {
}

void GameMaster::Render(sf::RenderWindow& window) {
}

void GameMaster::OnCollisionEnter(GameObject* other) {
}

void GameMaster::OnCollisionExit(GameObject* other) {
}