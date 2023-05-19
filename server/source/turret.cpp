#include "turret.h"
#include "game.h"
#include "world.h"

Turret* Turret::Create(pGame game, pWorld world, nlohmann::json& data) {
	uint32_t id = world->game_object_id++;

	world->game_objects[id] = std::make_unique<Turret>();
	world->dictionary[data.at("name")] = id;

	Turret* turret = static_cast<Turret*>(world->game_objects[id].get());

	turret->SetGame(game);
	turret->SetWorld(world);
	turret->SetId(id);
	turret->SetType(ACTOR_TURRET);
	turret->SetName(data.at("name"));
	turret->SetLayer(data.at("layer"));

	turret->Load(data.at("data_path"));
	turret->SetResourcePath(data.at("data_path"));

	turret->SetPosition(data.at("x"), data.at("y"));
	turret->SetTeam(data.at("team"));


	return turret;
}

void Turret::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);

	texture.loadFromFile("data/resources/textures/sample_turret1.png");
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
		//| FILTER_STRUCTURE
		//| FILTER_WALL
		//| FILTER_WATER
		//| FILTER_TREE
		//| FILTER_PICK_UP
		;

	fixture = body->CreateFixture(&fixture_def);
}

void Turret::Unload() {
	if (body != nullptr) {
		if (fixture != nullptr) {
			body->DestroyFixture(fixture);
			fixture = nullptr;
		}
		world->GetPhysics()->DestroyBody(body);
		body = nullptr;
	}
}

void Turret::Serialize(uint32_t tick) {
	auto& records_container = world->records[tick];
	records_container.push_back(
		std::make_unique<TurretRecord>(
			id, type
		)
	);
}

void Turret::Deserialize(Record* record) {
	auto turret_record = static_cast<TurretRecord*>(record);
}

void Turret::HandleInput(uint32_t tick) {
}

void Turret::ExecuteCommand(Command* command) {
}

void Turret::Update(float elapsed) {
}

void Turret::Render(sf::RenderWindow& window) {
	float render_x = 0.0f;
	float render_y = 0.0f;
	GetPosition(render_x, render_y);

	sprite.setPosition(
		render_x,
		-render_y + window.getSize().y
	);

	window.draw(sprite);
}

void Turret::OnCollisionEnter(GameObject* other) {
}

void Turret::OnCollisionExit(GameObject* other) {
}