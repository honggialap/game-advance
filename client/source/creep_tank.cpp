#include "creep_tank.h"
#include "game.h"
#include "world.h"

CreepTank::CreepTank(pGame game, pWorld world)
	: ClientGameObject(game, world) {
}

CreepTank::~CreepTank() {
}

CreepTank* CreepTank::Create(
	pGame game, pWorld world,
	std::string name,
	float position_x, float position_y,
	uint32_t layer,
	std::string data_path
) {
	uint32_t id = world->game_object_id++;

	world->game_objects[id] = std::make_unique<CreepTank>(game, world);
	world->dictionary[name] = id;

	CreepTank* creep_tank = static_cast<CreepTank*>(world->game_objects[id].get());
	creep_tank->SetName(name);
	creep_tank->SetId(id);
	creep_tank->SetType(ACTOR_CREEP_TANK);
	creep_tank->SetLayer(layer);
	creep_tank->Load(data_path);

	creep_tank->SetPosition(position_x, position_y);

	return creep_tank;
}

void CreepTank::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);

	texture.loadFromFile("data/resources/textures/sample_creep1.png");
	sprite.setTexture(texture);
	sprite.setOrigin(32, 32);

	body_def.type = b2_dynamicBody;
	body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	body = world->GetPhysics()->CreateBody(&body_def);

	collider.SetAsBox(32.0f / 30, 32.0f / 30);

	fixture_def.shape = &collider;
	fixture_def.density = 100.0f;
	fixture_def.friction = 0.0f;

	fixture_def.filter.categoryBits = FILTER_CREEP_TANK;
	fixture_def.filter.maskBits =
		FILTER_PLAYER_TANK
		| FILTER_CREEP_TANK
		| FILTER_BULLET
		| FILTER_STRUCTURE
		| FILTER_WALL
		| FILTER_WATER
		//| FILTER_TREE
		//| FILTER_PICK_UP
		;

	fixture = body->CreateFixture(&fixture_def);
}

void CreepTank::Unload() {
	if (body != nullptr) {
		if (fixture != nullptr) {
			body->DestroyFixture(fixture);
			fixture = nullptr;
		}
		world->GetPhysics()->DestroyBody(body);
		body = nullptr;
	}
}

void CreepTank::HandleInput(uint32_t tick) {
}

void CreepTank::ExecuteCommand(Command* command) {
}

void CreepTank::Update(float elapsed) {
}

void CreepTank::Render(sf::RenderWindow& window) {
	float render_x = 0.0f;
	float render_y = 0.0f;
	GetPosition(render_x, render_y);

	sprite.setPosition(
		render_x,
		-render_y + window.getSize().y
	);

	window.draw(sprite);
}

void CreepTank::OnCollisionEnter(GameObject* other) {
}

void CreepTank::OnCollisionExit(GameObject* other) {
}