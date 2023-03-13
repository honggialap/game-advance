#include "tank.h"
#include "game_client.h"
#include "world.h"

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

		animation.LoadTexture("data/resources/textures/test.png");
		animation.AddFrame(sf::IntRect(0, 0, 32, 32), 1000);
		animation.AddFrame(sf::IntRect(32, 0, 32, 32), 1000);
		animation.AddFrame(sf::IntRect(0, 32, 32, 32), 1000);
		animation.AddFrame(sf::IntRect(32, 32, 32, 32), 1000);
	}

	void Tank::Unload() {
	}

	void Tank::Update(float elapsed) {

		animation.Update(elapsed);

		// Animation control
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
			animation.Play(true);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
			animation.Play();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
			animation.Stop();
		}

		// Sprite movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			move(sf::Vector2f(0, 1.0f) * elapsed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			move(sf::Vector2f(0, -1.0f) * elapsed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			move(sf::Vector2f(-1.0f, 0) * elapsed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			move(sf::Vector2f(1.0f, 0) * elapsed);
		}
	}

	void Tank::Render(sf::RenderWindow& window) {
		animation.setPosition(
			getPosition().x,
			-getPosition().y + window.getSize().y
		);

		window.draw(animation);
	}

}