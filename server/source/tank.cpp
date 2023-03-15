#include "tank.h"
#include "game_server.h"
#include "world.h"

namespace Server {

	Tank::Tank(Engine::pGame game, Engine::pScene scene) 
	: Engine::GameObject(game, scene) {
		game_server = static_cast<pGameServer>(game);
		world = static_cast<pWorld>(scene);
	}

	Tank::~Tank() {
	}

	void Tank::Load(std::string data_path) {
		//std::ifstream data_file(data_path);
		//nlohmann::json data = nlohmann::json::parse(data_file);

		texture.loadFromFile("data/resources/textures/test.png", sf::IntRect(0, 0, 64, 64));
		texture.setSmooth(true);

		sprite.setTexture(texture);
		sprite.setPosition(100, 100);
	}

	void Tank::Unload() {
	}

	void Tank::Update(float elapsed) {
		// Camera movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			world->GetCamera().move(sf::Vector2f(0, -1.0f) * elapsed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			world->GetCamera().move(sf::Vector2f(0, 1.0f) * elapsed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			world->GetCamera().move(sf::Vector2f(-1.0f, 0) * elapsed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			world->GetCamera().move(sf::Vector2f(1.0f, 0) * elapsed);
		}

		// Sprite movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			sprite.move(sf::Vector2f(0, -1.0f) * elapsed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			sprite.move(sf::Vector2f(0, 1.0f) * elapsed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			sprite.move(sf::Vector2f(-1.0f, 0) * elapsed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			sprite.move(sf::Vector2f(1.0f, 0) * elapsed);
		}
	}

	void Tank::Render(sf::RenderWindow& window) {
		window.draw(sprite);
	}

	void Tank::OnCollisionEnter(Engine::pGameObject other) {
	}

	void Tank::OnCollisionExit(Engine::pGameObject other) {
	}

}