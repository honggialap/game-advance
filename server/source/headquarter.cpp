#include "headquarter.h"
#include "game.h"
#include "world.h"

Headquarter* Headquarter::Create(pGame game, pWorld world, nlohmann::json& data) {
	uint32_t id = world->game_object_id++;

	world->game_objects[id] = std::make_unique<Headquarter>();
	world->dictionary[data.at("name")] = id;

	Headquarter* headquarter = static_cast<Headquarter*>(world->game_objects[id].get());

	headquarter->SetGame(game);
	headquarter->SetWorld(world);
	headquarter->SetId(id);
	headquarter->SetType(ACTOR_HEADQUARTER);
	headquarter->SetName(data.at("name"));
	headquarter->SetLayer(data.at("layer"));

	headquarter->Load(data.at("data_path"));
	headquarter->SetResourcePath(data.at("data_path"));

	headquarter->SetPosition(data.at("x"), data.at("y"));
	headquarter->SetTeam(data.at("team"));


	return headquarter;
}

void Headquarter::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);

	texture.loadFromFile("data/resources/textures/sample_headquarter1.png");
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

void Headquarter::Unload() {
	if (body != nullptr) {
		if (fixture != nullptr) {
			body->DestroyFixture(fixture);
			fixture = nullptr;
		}
		world->GetPhysics()->DestroyBody(body);
		body = nullptr;
	}
}

void Headquarter::Serialize(uint32_t tick) {
	auto& records_container = world->records[tick];
	records_container.push_back(
		std::make_unique<HeadquarterRecord>(
			id, type
		)
	);
}

void Headquarter::Deserialize(Record* record) {
	auto headquarter_record = static_cast<HeadquarterRecord*>(record);
}

void Headquarter::HandleInput(uint32_t tick) {
}

void Headquarter::ExecuteCommand(Command* command) {
}

void Headquarter::Update(float elapsed) {
}

void Headquarter::Render(sf::RenderWindow& window) {
	float render_x = 0.0f;
	float render_y = 0.0f;
	GetPosition(render_x, render_y);

	sprite.setPosition(
		render_x,
		-render_y + window.getSize().y
	);

	window.draw(sprite);
}

void Headquarter::OnCollisionEnter(GameObject* other) {
}

void Headquarter::OnCollisionExit(GameObject* other) {
}