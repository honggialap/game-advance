#include "bound.h"
#include "game.h"
#include "world.h"

Bound* Bound::Create(
	pGame game, pWorld world,
	std::string name,
	float position_x, float position_y,
	uint32_t layer,
	std::string data_path
) {
	uint32_t id = world->game_object_id++;

	world->game_objects[id] = std::make_unique<Bound>();
	world->dictionary[name] = id;

	Bound* bound = static_cast<Bound*>(world->game_objects[id].get());
	bound->SetGame(game);
	bound->SetWorld(world);
	bound->SetName(name);
	bound->SetId(id);
	bound->SetType(ACTOR_BOUND);
	bound->SetLayer(layer);
	bound->Load(data_path);

	bound->SetPosition(position_x, position_y);

	return bound;
}

void Bound::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);

	body_def.type = b2_kinematicBody;
	body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	body = world->GetPhysics()->CreateBody(&body_def);

	collider.SetAsBox(32.0f / 30, 32.0f / 30);

	fixture_def.shape = &collider;
	fixture_def.density = 100.0f;
	fixture_def.friction = 0.0f;

	fixture_def.filter.categoryBits = FILTER_WALL;
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

void Bound::Unload() {
	if (body != nullptr) {
		if (fixture != nullptr) {
			body->DestroyFixture(fixture);
			fixture = nullptr;
		}
		world->GetPhysics()->DestroyBody(body);
		body = nullptr;
	}
}

void Bound::HandleInput(uint32_t tick) {
}

void Bound::ExecuteCommand(Command* command) {
}

void Bound::Update(float elapsed) {
}

void Bound::Render(sf::RenderWindow& window) {
}

void Bound::OnCollisionEnter(GameObject* other) {
}

void Bound::OnCollisionExit(GameObject* other) {
}
