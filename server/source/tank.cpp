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

	current_movement = sf::Vector2i(0, 0);
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

void Tank::Serialize(uint32_t tick) {
	float position_x;
	float position_y;
	GetPosition(position_x, position_y);

	float velocity_x;
	float velocity_y;
	GetVelocity(velocity_x, velocity_y);

	auto& records_container = world->records[tick];
	records_container.push_back(
		std::make_unique<TankRecord>(
			id,
			type,
			position_x,
			position_y,
			velocity_x,
			velocity_y,
			player_id,
			current_movement.x,
			current_movement.y
		)
	);
}

void Tank::Deserialize(Record* record) {
	auto tank_record = static_cast<TankRecord*>(record);
	SetPosition(tank_record->position_x, tank_record->position_y);
	SetVelocity(tank_record->velocity_x, tank_record->velocity_y);
	player_id = tank_record->player_id;
	current_movement.x = tank_record->current_movement_x;
	current_movement.y = tank_record->current_movement_y;
}

void Tank::HandleInput(uint32_t tick) {
}

void Tank::ExecuteCommand(Command* command) {
	switch (command->command_type) {
	case TANK_COMMAND_TYPE_MOVE: {
		auto move_command = static_cast<MoveCommand*>(command);
		current_movement.x = move_command->x;
		current_movement.y = move_command->y;
		break;
	}

	case TANK_COMMAND_TYPE_SHOOT: {
		auto shoot_command = static_cast<ShootCommand*>(command);
		break;
	}
	}
}

void Tank::Update(float elapsed) {
	b2Vec2 movement(
		speed * current_movement.x / 30.0f,
		speed * current_movement.y / 30.0f
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

void Tank::OnCollisionEnter(GameObject* other) {
	if (dynamic_cast<Wall*>(other)) {
		printf("TANK hit WALL.\n");
	}
}

void Tank::OnCollisionExit(GameObject* other) {
	if (dynamic_cast<Wall*>(other)) {
		printf("TANK stop hit WALL.\n");
	}
}
