#include "turret_bullet.h"
#include "game.h"
#include "world.h"

TurretBullet* TurretBullet::Create(pGame game, pWorld world, nlohmann::json& data) {
	uint32_t id = world->game_object_id++;

	world->game_objects[id] = std::make_unique<TurretBullet>();
	world->dictionary[data.at("name")] = id;

	TurretBullet* turret_bullet = static_cast<TurretBullet*>(world->game_objects[id].get());

	turret_bullet->SetGame(game);
	turret_bullet->SetWorld(world);
	turret_bullet->SetId(id);
	turret_bullet->SetType(ACTOR_TURRET_BULLET);
	turret_bullet->SetName(data.at("name"));
	turret_bullet->SetLayer(data.at("layer"));

	turret_bullet->Load(data.at("data_path"));
	turret_bullet->SetResourcePath(data.at("data_path"));

	turret_bullet->SetPosition(data.at("x"), data.at("y"));
	turret_bullet->SetTeam(data.at("team"));


	return turret_bullet;
}

void TurretBullet::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);

	texture.loadFromFile("data/resources/textures/sample_bullet1.png");
	sprite.setTexture(texture);
	sprite.setOrigin(32, 32);

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

void TurretBullet::Unload() {
	if (body != nullptr) {
		if (fixture != nullptr) {
			body->DestroyFixture(fixture);
			fixture = nullptr;
		}
		world->GetPhysics()->DestroyBody(body);
		body = nullptr;
	}
}

void TurretBullet::Serialize(uint32_t tick) {
	float position_x, position_y;
	GetPosition(position_x, position_y);

	float velocity_x, velocity_y;
	GetVelocity(velocity_x, velocity_y);

	auto& records_container = world->records[tick];
	records_container.push_back(
		std::make_unique<TurretBulletRecord>(
			id, type,
			position_x, position_y,
			velocity_x, velocity_y
		)
	);
}

void TurretBullet::Deserialize(Record* record) {
	auto turret_bullet_record = static_cast<TurretBulletRecord*>(record);
	SetPosition(turret_bullet_record->position_x, turret_bullet_record->position_y);
	SetVelocity(turret_bullet_record->velocity_x, turret_bullet_record->velocity_y);
}

void TurretBullet::HandleInput(uint32_t tick) {
}

void TurretBullet::ExecuteCommand(Command* command) {
}

void TurretBullet::Update(float elapsed) {
}

void TurretBullet::Render(sf::RenderWindow& window) {
	float render_x = 0.0f;
	float render_y = 0.0f;
	GetPosition(render_x, render_y);

	sprite.setPosition(
		render_x,
		-render_y + window.getSize().y
	);

	window.draw(sprite);
}

void TurretBullet::OnCollisionEnter(GameObject* other) {
}

void TurretBullet::OnCollisionExit(GameObject* other) {
}