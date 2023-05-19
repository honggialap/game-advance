#include "creep_bullet.h"
#include "game.h"
#include "world.h"

CreepBullet* CreepBullet::Create(pGame game, pWorld world, nlohmann::json& data) {
	uint32_t id = world->game_object_id++;

	world->game_objects[id] = std::make_unique<CreepBullet>();
	world->dictionary[data.at("name")] = id;

	CreepBullet* creep_bullet = static_cast<CreepBullet*>(world->game_objects[id].get());

	creep_bullet->SetGame(game);
	creep_bullet->SetWorld(world);
	creep_bullet->SetId(id);
	creep_bullet->SetType(ACTOR_CREEP_BULLET);
	creep_bullet->SetName(data.at("name"));
	creep_bullet->SetLayer(data.at("layer"));

	creep_bullet->Load(data.at("data_path"));
	creep_bullet->SetResourcePath(data.at("data_path"));

	creep_bullet->SetPosition(data.at("x"), data.at("y"));
	creep_bullet->SetTeam(data.at("team"));


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

	collider.SetAsBox(16.0f / 30, 16.0f / 30);

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

void CreepBullet::Serialize(uint32_t tick) {
	float position_x, position_y;
	GetPosition(position_x, position_y);

	float velocity_x, velocity_y;
	GetVelocity(velocity_x, velocity_y);

	auto& records_container = world->records[tick];
	records_container.push_back(
		std::make_unique<CreepBulletRecord>(
			id, type,
			position_x, position_y,
			velocity_x, velocity_y
		)
	);
}

void CreepBullet::Deserialize(Record* record) {
	auto creep_bullet_record = static_cast<CreepBulletRecord*>(record);
	SetPosition(creep_bullet_record->position_x, creep_bullet_record->position_y);
	SetVelocity(creep_bullet_record->velocity_x, creep_bullet_record->velocity_y);
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