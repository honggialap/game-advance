#include "player_bullet.h"
#include "game.h"
#include "world.h"

PlayerBullet* PlayerBullet::Create(
	pGame game, pWorld world,
	std::string name,
	float position_x, float position_y,
	uint32_t layer,
	std::string data_path
) {
	uint32_t id = world->game_object_id++;

	world->game_objects[id] = std::make_unique<PlayerBullet>();
	world->dictionary[name] = id;

	PlayerBullet* player_bullet = static_cast<PlayerBullet*>(world->game_objects[id].get());
	player_bullet->SetGame(game);
	player_bullet->SetWorld(world);
	player_bullet->SetName(name);
	player_bullet->SetId(id);
	player_bullet->SetType(ACTOR_PLAYER_BULLET);
	player_bullet->SetLayer(layer);
	player_bullet->Load(data_path);

	player_bullet->SetPosition(position_x, position_y);

	return player_bullet;
}

void PlayerBullet::Load(std::string data_path) {
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

void PlayerBullet::Unload() {
	if (body != nullptr) {
		if (fixture != nullptr) {
			body->DestroyFixture(fixture);
			fixture = nullptr;
		}
		world->GetPhysics()->DestroyBody(body);
		body = nullptr;
	}
}

void PlayerBullet::HandleInput(uint32_t tick) {
}

void PlayerBullet::ExecuteCommand(Command* command) {
}

void PlayerBullet::Update(float elapsed) {
}

void PlayerBullet::Render(sf::RenderWindow& window) {
	float render_x = 0.0f;
	float render_y = 0.0f;
	GetPosition(render_x, render_y);

	sprite.setPosition(
		render_x,
		-render_y + window.getSize().y
	);

	window.draw(sprite);
}

void PlayerBullet::OnCollisionEnter(GameObject* other) {
}

void PlayerBullet::OnCollisionExit(GameObject* other) {
}
