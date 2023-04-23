#include "tank.h"
#include "game.h"
#include "world.h"

#include "bullet.h"
#include "wall.h"

void Tank::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);

	texture.loadFromFile("data/resources/textures/test.png");
	sprite.setTexture(texture);
	sprite.setOrigin(32, 32);

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

pGameObjectState Tank::Serialize() {
	float position_x;
	float position_y;
	GetPosition(position_x, position_y);

	float velocity_x;
	float velocity_y;
	GetVelocity(velocity_x, velocity_y);
	
	return new TankState(
		id,
		type,
		position_x,
		position_y,
		velocity_x,
		velocity_y,
		player_id,
		current_movement.x,
		current_movement.y
	);
}

void Tank::Deserialize(pGameObjectState game_object_state) {
	auto tank_state = static_cast<pTankState>(game_object_state);
	SetPosition(tank_state->position_x, tank_state->position_y);
	SetVelocity(tank_state->velocity_x, tank_state->velocity_y);
	player_id = tank_state->player_id;
	current_movement.x = tank_state->current_movement_x;
	current_movement.y = tank_state->current_movement_y;
}

void Tank::ExecuteCommand(uint32_t tick) {
	if (commands.empty()) {
		return;
	}

	auto command = commands.front();
	if (command->tick == tick) {
		switch (command->type) {
		case Command::Move: {
			auto move_command = static_cast<pMoveCommand>(command);
			current_movement.x = move_command->x;
			current_movement.y = move_command->y;

			delete move_command;
			commands.pop_front();
			break;
		}
		}
	}
}

void Tank::Update(float elapsed) {
	// Movement control
	b2Vec2 movement(
		current_movement.x / 30.0f,
		current_movement.y / 30.0f
	);
	body->SetLinearVelocity(movement);
}

void Tank::Render(sf::RenderWindow& window) {
	float render_x = 0.0f;
	float render_y = 0.0f;
	GetPosition(render_x, render_y);

	sprite.setPosition(
		render_x,
		-render_y + window.getSize().y
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
