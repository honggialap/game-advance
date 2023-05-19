#include "factory.h"
#include "game.h"
#include "world.h"

Factory* Factory::Create(pGame game, pWorld world, nlohmann::json& data) {
	uint32_t id = world->game_object_id++;

	world->game_objects[id] = std::make_unique<Factory>();
	world->dictionary[data.at("name")] = id;

	Factory* factory = static_cast<Factory*>(world->game_objects[id].get());

	factory->SetGame(game);
	factory->SetWorld(world);
	factory->SetId(id);
	factory->SetType(ACTOR_FACTORY);
	factory->SetName(data.at("name"));
	factory->SetLayer(data.at("layer"));

	factory->Load(data.at("data_path"));
	factory->SetResourcePath(data.at("data_path"));

	factory->SetPosition(data.at("x"), data.at("y"));
	factory->SetTeam(data.at("team"));

	return factory;
}

void Factory::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);

	texture.loadFromFile("data/resources/textures/sample_factory1.png");
	sprite.setTexture(texture);
	sprite.setOrigin(32, 32);

	body_def.type = b2_kinematicBody;
	body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	body = world->GetPhysics()->CreateBody(&body_def);

	collider.SetAsBox(32.0f / 30, 32.0f / 30);

	fixture_def.shape = &collider;
	fixture_def.density = 100.0f;
	fixture_def.friction = 0.0f;

	fixture_def.filter.categoryBits = FILTER_STRUCTURE;
	fixture_def.filter.maskBits =
		FILTER_PLAYER_TANK
		| FILTER_CREEP_TANK
		| FILTER_BULLET
		| FILTER_STRUCTURE
		//| FILTER_WALL
		//| FILTER_WATER
		//| FILTER_TREE
		//| FILTER_PICK_UP
		;

	fixture = body->CreateFixture(&fixture_def);
}

void Factory::Unload() {
	if (body != nullptr) {
		if (fixture != nullptr) {
			body->DestroyFixture(fixture);
			fixture = nullptr;
		}
		world->GetPhysics()->DestroyBody(body);
		body = nullptr;
	}
}

void Factory::Serialize(uint32_t tick) {
	auto& records_container = world->records[tick];
	records_container.push_back(
		std::make_unique<FactoryRecord>(
			id, type
		)
	);
}

void Factory::Deserialize(Record* record) {
	auto factory_record = static_cast<FactoryRecord*>(record);
}

void Factory::HandleInput(uint32_t tick) {
}

void Factory::ExecuteCommand(Command* command) {
}

void Factory::Update(float elapsed) {
}

void Factory::Render(sf::RenderWindow& window) {
	float render_x = 0.0f;
	float render_y = 0.0f;
	GetPosition(render_x, render_y);

	sprite.setPosition(
		render_x,
		-render_y + window.getSize().y
	);

	window.draw(sprite);
}

void Factory::OnCollisionEnter(GameObject* other) {
}

void Factory::OnCollisionExit(GameObject* other) {
}