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

void Tank::HandleInput() {

	if (player_control) {
		sf::Vector2i movement(0, 0);
		switch (game->player_id) {
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
			current_movement.x = movement.x;
			current_movement.y = movement.y;

			auto move_command = new MoveCommand(0, GetId(), current_movement.x, current_movement.y);
			world->commands.push_back(move_command);
			SendMoveCommand(move_command);
		}
	}
}

void Tank::Update(float elapsed) {
	HandleInput();
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

void Tank::SendMoveCommand(pMoveCommand move_command) {
	auto move_command_packet = std::make_shared<Packet>(PacketType::PlayerMove);
	*move_command_packet
		<< game->GetId()
		<< player_id
		<< move_command->tick
		<< move_command->type
		<< move_command->id
		<< move_command->x
		<< move_command->y
		;
	game->Send(move_command_packet);
}
