#include "tank.h"
#include "game_client.h"
#include "world.h"

#include "wall.h"

namespace Client {
	
	Tank::Tank(Engine::pGame game, Engine::pScene scene)
		: Engine::GameObject(game, scene) {
		game_client = static_cast<pGameClient>(game);
		world = static_cast<pWorld>(scene);
	}

	Tank::~Tank() {
	}

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
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			movement.y += 0.01f / 30 * elapsed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			movement.y += -0.01f / 30 * elapsed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			movement.x += -0.01f / 30 * elapsed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			movement.x += 0.01f / 30 * elapsed;
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

	void Tank::OnCollisionEnter(Engine::pGameObject other) {
		if (dynamic_cast<pWall>(other)) {
			printf("TANK hit WALL.\n");
		}
	}

	void Tank::OnCollisionExit(Engine::pGameObject other) {
		if (dynamic_cast<pWall>(other)) {
			printf("TANK stop hit WALL.\n");
		}
	}

}