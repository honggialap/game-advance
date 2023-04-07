#include "tank.h"
#include "game.h"
#include "world.h"

#include "wall.h"

void Tank::Load(std::string data_path) {
	//std::ifstream data_file(data_path);
	//nlohmann::json data = nlohmann::json::parse(data_file);

	texture.loadFromFile("data/resources/textures/test.png");
	sprite.setTexture(texture);
	sprite.setOrigin(32, 32);

	setPosition(0, 0);

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
	setPosition(
		body->GetPosition().x * 30,
		body->GetPosition().y * 30
	);

	// Movement control
	b2Vec2 movement(0, 0);
	if (player_control) {
		int32_t current_movement_x = 0;
		int32_t current_movement_y = 0;

		switch (game->GetId()) {
		case 1000: {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				current_movement_y = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				current_movement_y = -1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				current_movement_x = -1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				current_movement_x = 1;
			}
			break;
		}

		case 1001: {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
				current_movement_y = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
				current_movement_y = -1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
				current_movement_x = -1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
				current_movement_x = 1;
			}
			break;
		}

		case 1002: {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
				current_movement_y = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
				current_movement_y = -1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
				current_movement_x = -1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
				current_movement_x = 1;
			}
			break;
		}

		default: {
			break;
		}

		}

		if (
			(movement_x != current_movement_x)
			|| (movement_y != current_movement_y)
			) {
			movement_x = current_movement_x;
			movement_y = current_movement_y;

			if (sync) {
				auto player_move_packet = std::make_shared<Packet>(PacketType::PlayerMove);
				*player_move_packet << game->GetId() << networks_id << movement_x << movement_y;
				game->Send(player_move_packet);
			}
		}

		movement = b2Vec2(
			movement_x * 0.01f / 30 * elapsed, 
			movement_y * 0.01f / 30 * elapsed
		);

		
	}
	else {
		if (sync) {
			movement = b2Vec2(
				movement_x * 0.01f / 30 * elapsed,
				movement_y * 0.01f / 30 * elapsed
			);
		}
	}

	body->SetLinearVelocity(movement);
}

void Tank::Render(sf::RenderWindow& window) {
	sprite.setPosition(
		getPosition().x,
		-getPosition().y + window.getSize().y
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
