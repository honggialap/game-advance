#include "tank.h"
#include "game.h"
#include "world.h"

#include "bullet.h"
#include "wall.h"

pGameObjectState Tank::Serialize() {
	return new TankState(
		id,
		type,
		position_x,
		position_y,
		velocity_x,
		velocity_y,
		player_id
	);
}

bool Tank::Deserialize(pGameObjectState game_object_state) {
	if (!static_cast<pTankState>(game_object_state)) {
		return false;
	}

	pTankState state = static_cast<pTankState>(game_object_state);
	position_x = state->position_x;
	position_y = state->position_y;
	velocity_x = state->velocity_x;
	velocity_y = state->velocity_y;
	player_id = state->player_id;

	return true;
}

void Tank::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);

	texture.loadFromFile("data/resources/textures/test.png");
	sprite.setTexture(texture);
	sprite.setOrigin(32, 32);

	SetPosition(0, 0);

	body_def.position.Set(0, 0);
	body_def.type = b2_dynamicBody;
	body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	body = world->GetPhysics()->CreateBody(&body_def);

	collider.SetAsBox(32.0f / 30, 32.0f / 30);

	fixture_def.shape = &collider;
	fixture_def.density = 100.0f;
	fixture_def.friction = 0.0f;

	fixture = body->CreateFixture(&fixture_def);
}

void Tank::Unload() {
	if (body != nullptr) {
		if (fixture != nullptr) {
			body->DestroyFixture(fixture);
			fixture = nullptr;
		}
		world->GetPhysics()->DestroyBody(body);
		body = nullptr;
	}
}

void Tank::Update(float elapsed) {
	SetPosition(
		body->GetPosition().x * 30,
		body->GetPosition().y * 30
	);

	// Movement control
	b2Vec2 movement(0, 0);
	body->SetLinearVelocity(movement);
}

void Tank::Render(sf::RenderWindow& window) {
	sprite.setPosition(
		position_x,
		-position_y + window.getSize().y
	);

	window.draw(sprite);
}

void Tank::OnCollisionEnter(pGameObject other) {
	if (dynamic_cast<pWall>(other)) {
		printf("TANK hit WALL.\n");
	}
}

void Tank::OnCollisionExit(pGameObject other) {
	if (dynamic_cast<pWall>(other)) {
		printf("TANK stop hit WALL.\n");
	}
}
