#include "player_tank.h"
#include "game.h"
#include "world.h"

#include "player_bullet.h"
#include "wall.h"

PlayerTank::PlayerTank(Game* game, World* world)
	: ClientGameObject(game, world) {
}

PlayerTank::~PlayerTank() {
}

PlayerTank* PlayerTank::Create(
	pGame game, pWorld world,
	std::string name,
	float position_x, float position_y,
	uint32_t layer,
	std::string data_path
) {
	uint32_t id = world->game_object_id++;

	world->game_objects[id] = std::make_unique<PlayerTank>(game, world);
	world->dictionary[name] = id;

	PlayerTank* player_tank = static_cast<PlayerTank*>(world->game_objects[id].get());
	player_tank->SetName(name);
	player_tank->SetId(id);
	player_tank->SetType(ACTOR_PLAYER_TANK);
	player_tank->SetLayer(layer);
	player_tank->Load(data_path);

	player_tank->SetPosition(position_x, position_y);

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

void PlayerTank::HandleInput(uint32_t tick) {
	if (player_control) {
		sf::Vector2i movement(0, 0);
		switch (game_client->GetPlayerId()) {
		case 1: {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				movement.y = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				movement.y = -1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				movement.x = -1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				movement.x = 1;
			}
			break;
		}

		case 2: {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
				movement.y = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
				movement.y = -1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
				movement.x = -1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
				movement.x = 1;
			}
			break;
		}

		case 3: {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
				movement.y = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
				movement.y = -1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
				movement.x = -1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
				movement.x = 1;
			}
			break;
		}

		case 4: {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				movement.y = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				movement.y = -1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				movement.x = -1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				movement.x = 1;
			}
			break;
		}

		}

		if (movement.x != current_movement.x
			|| movement.y != current_movement.y) {
			MoveCommand move_command(id, movement.x, movement.y);

			world->commands[tick].push_back(
				std::make_unique<MoveCommand>(move_command)
			);
			SendMoveCommand(tick, move_command);
		}
	}
}

void PlayerTank::ExecuteCommand(Command* command) {
	switch (command->command_type) {
	case PLAYER_TANK_COMMAND_MOVE: {
		auto move_command = static_cast<MoveCommand*>(command);
		current_movement.x = move_command->x;
		current_movement.y = move_command->y;
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
	if (player_control) {
		float render_x = 0.0f;
		float render_y = 0.0f;
		GetPosition(render_x, render_y);

		sprite.setPosition(
			render_x,
			-render_y + window.getSize().y
		);
	}
	else {
		uint32_t latest_tick = world->latest_tick;
		uint32_t server_tick = world->server_tick;
		uint32_t tick_per_game_state = world->tick_per_game_state;

		float interval = (float(latest_tick) - float(server_tick) - float(tick_per_game_state)) / float(tick_per_game_state);

		float render_x = last_known_x + ((latest_x - last_known_x) * interval);
		float render_y = last_known_y + ((latest_y - last_known_y) * interval);

		sprite.setPosition(
			render_x,
			-render_y + window.getSize().y
		);
	}

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

void PlayerTank::SendMoveCommand(uint32_t tick, MoveCommand move_command) {
	auto move_command_packet = std::make_shared<Packet>(PacketType::PlayerMove);
	*move_command_packet
		<< game_client->GetClientId()
		<< player_id
		<< tick
		<< move_command.game_object_id
		<< move_command.command_type
		<< move_command.x
		<< move_command.y
		;
	game_client->Send(move_command_packet);
}