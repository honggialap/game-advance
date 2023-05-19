#include "player_tank.h"
#include "game.h"
#include "world.h"

#include "player_bullet.h"
#include "wall.h"

PlayerTank* PlayerTank::Create(pGame game, pWorld world, nlohmann::json& data) {
	uint32_t id = world->game_object_id++;

	world->game_objects[id] = std::make_unique<PlayerTank>();
	world->dictionary[data.at("name")] = id;

	PlayerTank* player_tank = static_cast<PlayerTank*>(world->game_objects[id].get());

	player_tank->SetGame(game);
	player_tank->SetWorld(world);
	player_tank->SetId(id);
	player_tank->SetType(ACTOR_PLAYER_TANK);
	player_tank->SetName(data.at("name"));
	player_tank->SetLayer(data.at("layer"));

	player_tank->Load(data.at("data_path"));
	player_tank->SetResourcePath(data.at("data_path"));

	player_tank->SetPosition(data.at("x"), data.at("y"));
	player_tank->SetPlayerId(data.at("player_id"));
	player_tank->SetTeam(data.at("team"));

	return player_tank;
}

void PlayerTank::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);

	texture.loadFromFile("data/resources/textures/sample_tank1.png");
	sprite.setTexture(texture);
	sprite.setOrigin(32, 32);

	body_def.type = b2_dynamicBody;
	body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	body = world->GetPhysics()->CreateBody(&body_def);

	collider.SetAsBox(32.0f / 30, 32.0f / 30);

	fixture_def.shape = &collider;
	fixture_def.density = 100.0f;
	fixture_def.friction = 0.0f;

	fixture_def.filter.categoryBits = FILTER_PLAYER_TANK;
	fixture_def.filter.maskBits =
		FILTER_PLAYER_TANK
		| FILTER_CREEP_TANK
		| FILTER_BULLET
		| FILTER_STRUCTURE
		| FILTER_WALL
		| FILTER_WATER
		//| FILTER_TREE
		| FILTER_PICK_UP
		;

	fixture = body->CreateFixture(&fixture_def);

	current_movement = sf::Vector2i(0, 0);
}

void PlayerTank::Unload() {
	if (body != nullptr) {
		if (fixture != nullptr) {
			body->DestroyFixture(fixture);
			fixture = nullptr;
		}
		world->GetPhysics()->DestroyBody(body);
		body = nullptr;
	}
}

void PlayerTank::Serialize(uint32_t tick) {
	float position_x, position_y;
	GetPosition(position_x, position_y);

	float velocity_x, velocity_y;
	GetVelocity(velocity_x, velocity_y);

	int32_t movement_x, movement_y;
	GetMovement(movement_x, movement_y);

	auto& records_container = world->records[tick];
	records_container.push_back(
		std::make_unique<PlayerTankRecord>(
			id, type,
			position_x, position_y,
			velocity_x, velocity_y,
			movement_x, movement_y
		)
	);
}

void PlayerTank::Deserialize(Record* record) {
	auto tank_record = static_cast<PlayerTankRecord*>(record);
	SetPosition(tank_record->position_x, tank_record->position_y);
	SetVelocity(tank_record->velocity_x, tank_record->velocity_y);
	SetMovement(tank_record->movement_x, tank_record->movement_y);
}

void PlayerTank::HandleInput(uint32_t tick) {
}

void PlayerTank::ExecuteCommand(Command* command) {
	switch (command->command_type) {
	case PLAYER_TANK_COMMAND_MOVE: {
		auto move_command = static_cast<MoveCommand*>(command);
		SetMovement(move_command->x, move_command->y);
		break;
	}

	case PLAYER_TANK_COMMAND_SHOOT: {
		auto shoot_command = static_cast<ShootCommand*>(command);
		break;
	}
	}
}

void PlayerTank::Update(float elapsed) {
	b2Vec2 movement(
		speed * current_movement.x / 30.0f,
		speed * current_movement.y / 30.0f
	);
	body->SetLinearVelocity(movement);
}

void PlayerTank::Render(sf::RenderWindow& window) {
	float render_x = 0.0f;
	float render_y = 0.0f;
	GetPosition(render_x, render_y);

	sprite.setPosition(
		render_x,
		-render_y + window.getSize().y
	);

	window.draw(sprite);
}

void PlayerTank::OnCollisionEnter(GameObject* other) {
	if (dynamic_cast<Wall*>(other)) {
		printf("TANK hit WALL.\n");
	}
}

void PlayerTank::OnCollisionExit(GameObject* other) {
	if (dynamic_cast<Wall*>(other)) {
		printf("TANK stop hit WALL.\n");
	}
}
