#include "repair_kit.h"
#include "game.h"
#include "world.h"

RepairKit* RepairKit::Create(
	pGame game, pWorld world,
	std::string name,
	float position_x, float position_y,
	uint32_t layer,
	std::string data_path
) {
	uint32_t id = world->game_object_id++;

	world->game_objects[id] = std::make_unique<RepairKit>();
	world->dictionary[name] = id;

	RepairKit* repair_kit = static_cast<RepairKit*>(world->game_objects[id].get());
	repair_kit->SetGame(game);
	repair_kit->SetWorld(world);
	repair_kit->SetName(name);
	repair_kit->SetId(id);
	repair_kit->SetType(ACTOR_REPAIR_KIT);
	repair_kit->SetLayer(layer);
	repair_kit->Load(data_path);

	repair_kit->SetPosition(position_x, position_y);

	return repair_kit;
}

void RepairKit::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);

	texture.loadFromFile("data/resources/textures/sample_repair_kit.png");
	sprite.setTexture(texture);
	sprite.setOrigin(32, 32);

	body_def.type = b2_kinematicBody;
	body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	body = world->GetPhysics()->CreateBody(&body_def);

	collider.SetAsBox(32.0f / 30, 32.0f / 30);

	fixture_def.shape = &collider;
	fixture_def.density = 100.0f;
	fixture_def.friction = 0.0f;

	fixture_def.filter.categoryBits = FILTER_PICK_UP;
	fixture_def.filter.maskBits = 
		FILTER_PLAYER_TANK
		//| FILTER_CREEP_TANK
		//| FILTER_BULLET
		//| FILTER_STRUCTURE
		//| FILTER_WALL
		//| FILTER_WATER
		//| FILTER_TREE
		//| FILTER_PICK_UP
		;

	fixture = body->CreateFixture(&fixture_def);
}

void RepairKit::Unload() {
	if (body != nullptr) {
		if (fixture != nullptr) {
			body->DestroyFixture(fixture);
			fixture = nullptr;
		}
		world->GetPhysics()->DestroyBody(body);
		body = nullptr;
	}
}

void RepairKit::HandleInput(uint32_t tick) {
}

void RepairKit::ExecuteCommand(Command* command) {
}

void RepairKit::Update(float elapsed) {
}

void RepairKit::Render(sf::RenderWindow& window) {
	float render_x = 0.0f;
	float render_y = 0.0f;
	GetPosition(render_x, render_y);

	sprite.setPosition(
		render_x,
		-render_y + window.getSize().y
	);

	window.draw(sprite);
}

void RepairKit::OnCollisionEnter(GameObject* other) {
}

void RepairKit::OnCollisionExit(GameObject* other) {
}
