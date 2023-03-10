#include "bullet.h"
#include "game_client.h"
#include "world.h"

namespace Client {

	Bullet::Bullet(Engine::pGame game, Engine::pScene scene)
		: Engine::GameObject(game, scene) {
		game_client = static_cast<pGameClient>(game);
		world = static_cast<pWorld>(scene);
	}

	Bullet::~Bullet() {
	}

	void Bullet::Load(std::string data_path) {
		//std::ifstream data_file(data_path);
		//nlohmann::json data = nlohmann::json::parse(data_file);

		font.loadFromFile("data/resources/fonts/arial.ttf");

		text.setFont(font);
		text.setString("TESTING FONT");
		text.setFillColor(sf::Color::Red);
		text.setPosition(200, 200);
	}

	void Bullet::Unload() {
	}

	void Bullet::Update(float elapsed) {
		// Scene control
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
			game->PlayScene(0);
		}
	}

	void Bullet::Render(sf::RenderWindow& window) {
		window.draw(text);
	}

}