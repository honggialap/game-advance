#include "power_up.h"
#include "game.h"
#include "world.h"

PowerUp::PowerUp(Game* game, World* world)
	: ClientGameObject(game, world) {
}

PowerUp::~PowerUp() {
}

PowerUp* PowerUp::Create(
	pGame game, pWorld world,
	std::string name,
	float position_x, float position_y,
	uint32_t layer,
	std::string data_path
) {
	uint32_t id = world->game_object_id++;

	world->game_objects[id] = std::make_unique<PowerUp>(game, world);
	world->dictionary[name] = id;

	PowerUp* power_up = static_cast<PowerUp*>(world->game_objects[id].get());
	power_up->SetName(name);
	power_up->SetId(id);
	power_up->SetType(ACTOR_POWER_UP);
	power_up->SetLayer(layer);
	power_up->Load(data_path);

	power_up->SetPosition(position_x, position_y);

	return power_up;
}

void PowerUp::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);

	texture.loadFromFile("data/resources/textures/sample_power_up.png");
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

void PowerUp::Unload() {
	if (body != nullptr) {
		if (fixture != nullptr) {
			body->DestroyFixture(fixture);
			fixture = nullptr;
		}
		world->GetPhysics()->DestroyBody(body);
		body = nullptr;
	}
}

void PowerUp::HandleInput(uint32_t tick) {
}

void PowerUp::ExecuteCommand(Command* command) {
}

void PowerUp::Update(float elapsed) {
}

void PowerUp::Render(sf::RenderWindow& window) {
	float render_x = 0.0f;
	float render_y = 0.0f;
	GetPosition(render_x, render_y);

	sprite.setPosition(
		render_x,
		-render_y + window.getSize().y
	);

	window.draw(sprite);
}

void PowerUp::OnCollisionEnter(GameObject* other) {
}

void PowerUp::OnCollisionExit(GameObject* other) {
}
