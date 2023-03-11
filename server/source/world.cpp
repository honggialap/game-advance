#include "world.h"
#include "game_server.h"
#include "tank.h"
#include "bullet.h"
#include "wall.h"

namespace Server {

	World::World(Engine::pGame game) : Engine::Scene(game) {
		game_server = static_cast<pGameServer>(game);
	}

	World::~World() {
	}

	Engine::pGameObject World::CreateGameObject(unsigned int game_object_type) {
		switch (game_object_type) {
		case ACTOR_TYPE_TANK:
			return new Tank(game_server, this);
			break;

		case ACTOR_TYPE_BULLET:
			return new Bullet(game_server, this);
			break;

		case ACTOR_TYPE_WALL:
			return new Wall(game_server, this);
			break;

		default:
			return nullptr;
			break;
		}
	}

	void World::Load(std::string data_path) {
		std::ifstream data_file(data_path);
		nlohmann::json data = nlohmann::json::parse(data_file);

		camera.reset(sf::FloatRect(0, 0, 800, 600));
		camera.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

		tank.reset(CreateGameObject(ACTOR_TYPE_TANK));
		tank->Load("");
		
		bullet.reset(CreateGameObject(ACTOR_TYPE_BULLET));
		bullet->Load("");
		
		wall.reset(CreateGameObject(ACTOR_TYPE_WALL));
		wall->Load("");
	}

	void World::Unload() {
		tank->Unload();
		tank.reset();
		
		bullet->Unload();
		bullet.reset();
		
		wall->Unload();
		wall.reset();
	}

	void World::Update(float elapsed) {
		tank->Update(elapsed);
		bullet->Update(elapsed);
		wall->Update(elapsed);
	}

	void World::Render(sf::RenderWindow& window) {
		window.setView(camera);
		tank->Render(window);
		bullet->Render(window);
		wall->Render(window);
	}

	sf::View& World::GetCamera() {
		return camera;
	}

}