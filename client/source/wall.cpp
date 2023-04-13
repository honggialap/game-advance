#include "wall.h"
#include "game.h"
#include "world.h"

#include "tank.h"

pGameObjectState Wall::Serialize() {
	return new WallState(
		id,
		type,
		position_x,
		position_y,
		velocity_x,
		velocity_y
	);
}

bool Wall::Deserialize(pGameObjectState game_object_state) {
	if (!static_cast<pWallState>(game_object_state)) {
		return false;
	}

	pWallState state = static_cast<pWallState>(game_object_state);
	position_x = state->position_x;
	position_y = state->position_y;
	velocity_x = state->velocity_x;
	velocity_y = state->velocity_y;

	return true;
}

void Wall::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);

	texture.loadFromFile("data/resources/textures/test_wall.png");
	sprite.setTexture(texture);
	sprite.setOrigin(32, 32);

	SetPosition(0, 0);

	body_def.position.Set(0, 0);
	body_def.type = b2_kinematicBody;
	body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	body = world->GetPhysics()->CreateBody(&body_def);

	collider.SetAsBox(32.0f / 30, 32.0f / 30);

	fixture_def.shape = &collider;
	fixture_def.density = 100.0f;
	fixture_def.friction = 0.0f;

	fixture = body->CreateFixture(&fixture_def);
}

void Wall::Unload() {
	if (body != nullptr) {
		if (fixture != nullptr) {
			body->DestroyFixture(fixture);
			fixture = nullptr;
		}
		world->GetPhysics()->DestroyBody(body);
		body = nullptr;
	}
}

void Wall::Update(float elapsed) {
	SetPosition(
		body->GetPosition().x * 30,
		body->GetPosition().y * 30
	);
}

void Wall::Render(sf::RenderWindow& window) {
	sprite.setPosition(
		position_x,
		-position_y + window.getSize().y
	);

	window.draw(sprite);
}

void Wall::OnCollisionEnter(pGameObject other) {
	if (dynamic_cast<pTank>(other)) {
		printf("WALL block TANK.\n");
	}
}

void Wall::OnCollisionExit(pGameObject other) {
	if (dynamic_cast<pTank>(other)) {
		printf("WALL stop block TANK.\n");
	}
}
