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

	body_def.position.Set(position_x / 30.0f , position_y / 30.0f);
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
}

void Tank::Update(float elapsed) {
	SetPosition(
		body->GetPosition().x * 30,
		body->GetPosition().y * 30
	);

	// Movement control
	b2Vec2 movement(
		current_movement.x / 30.0f,
		current_movement.y / 30.0f
	);
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
