#include "wall.h"
#include "game_client.h"
#include "world.h"

namespace Client {

	Wall::Wall(Engine::pGame game, Engine::pScene scene)
		: Engine::GameObject(game, scene) {
		game_client = static_cast<pGameClient>(game);
		world = static_cast<pWorld>(scene);
	}

	Wall::~Wall() {
	}

	void Wall::Load(std::string data_path) {
		//std::ifstream data_file(data_path);
		//nlohmann::json data = nlohmann::json::parse(data_file);

		texture.loadFromFile("data/resources/textures/test_wall.png");
		sprite.setTexture(texture);
		sprite.setOrigin(32, 32);

		setPosition(0, 0);

		body_def.position.Set(0, 0);
		body_def.type = b2_kinematicBody;

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
		setPosition(
			body->GetPosition().x * 30,
			body->GetPosition().y * 30
		);
	}

	void Wall::Render(sf::RenderWindow& window) {
		sprite.setPosition(
			getPosition().x,
			-getPosition().y + window.getSize().y
		);

		window.draw(sprite);
	}

}