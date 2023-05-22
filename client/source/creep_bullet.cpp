#include "creep_bullet.h"
#include "game.h"
#include "world.h"

CreepBullet::CreepBullet(pGame game, pWorld world) 
	: ClientGameObject(game, world) {
}

CreepBullet::~CreepBullet() {
}

CreepBullet* CreepBullet::Create(
	pGame game, pWorld world,
	std::string name,
	float position_x, float position_y,
	uint32_t layer,
	std::string data_path
) {
	uint32_t id = world->game_object_id++;

	world->game_objects[id] = std::make_unique<CreepBullet>(game, world);
	world->dictionary[name] = id;

	CreepBullet* creep_bullet = static_cast<CreepBullet*>(world->game_objects[id].get());
	creep_bullet->SetName(name);
	creep_bullet->SetId(id);
	creep_bullet->SetType(ACTOR_CREEP_BULLET);
	creep_bullet->SetLayer(layer);
	creep_bullet->Load(data_path);

	creep_bullet->SetPosition(position_x, position_y);

	return creep_bullet;
}

void CreepBullet::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);

	texture.loadFromFile("data/resources/textures/sample_bullet1.png");
	sprite.setTexture(texture);
	sprite.setOrigin(16, 16);

	body_def.type = b2_dynamicBody;
	body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	body = world->GetPhysics()->CreateBody(&body_def);

	collider.SetAsBox(32.0f / 30, 32.0f / 30);

	fixture_def.shape = &collider;
	fixture_def.density = 100.0f;
	fixture_def.friction = 0.0f;

	fixture_def.filter.categoryBits = FILTER_BULLET;
	fixture_def.filter.maskBits =
		FILTER_PLAYER_TANK
		| FILTER_CREEP_TANK
		| FILTER_BULLET
		| FILTER_STRUCTURE
		| FILTER_WALL
		//| FILTER_WATER
		//| FILTER_TREE
		//| FILTER_PICK_UP
		;

	fixture = body->CreateFixture(&fixture_def);
}

void CreepBullet::Unload() {
	if (body != nullptr) {
		if (fixture != nullptr) {
			body->DestroyFixture(fixture);
			fixture = nullptr;
		}
		world->GetPhysics()->DestroyBody(body);
		body = nullptr;
	}
}

void CreepBullet::HandleInput(uint32_t tick) {
}

void CreepBullet::ExecuteCommand(Command* command) {
}

void CreepBullet::Update(float elapsed) {
}

void CreepBullet::Render(sf::RenderWindow& window) {
	float render_x = 0.0f;
	float render_y = 0.0f;
	GetPosition(render_x, render_y);

	sprite.setPosition(
		render_x,
		-render_y + window.getSize().y
	);

	window.draw(sprite);
}

void CreepBullet::OnCollisionEnter(GameObject* other) {
}

void CreepBullet::OnCollisionExit(GameObject* other) {
}
