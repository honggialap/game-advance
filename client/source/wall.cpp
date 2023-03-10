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

		sfx_buffer.loadFromFile("data/resources/audios/sfx.wav");
		sfx.setBuffer(sfx_buffer);

		music.openFromFile("data/resources/audios/audio.wav");
	}

	void Wall::Unload() {
	}

	void Wall::Update(float elapsed) {
		// Sound control
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
			sfx.play();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
			music.play();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
			music.stop();
		}
	}

	void Wall::Render(sf::RenderWindow& window) {
	}

}