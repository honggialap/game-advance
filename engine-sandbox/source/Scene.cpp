#include "Scene.h"

#include "Game.h"

Scene::Scene(pGame game) : game(game) {
}

Scene::~Scene()
{
}

sf::View& Scene::GetCamera() {
	return camera;
}

void Scene::Load(std::string data_path) {
	camera.reset(sf::FloatRect(0, 0, 800, 600));
	gameObject = std::make_unique<GameObject>(game, this);
	gameObject->Load();
}

void Scene::Unload() {
	gameObject->Unload();
}

void Scene::Update(float elapsed) {
	gameObject->Update(elapsed);
}

void Scene::Render(sf::RenderWindow& window) {
	window.setView(camera);

	gameObject->Render(window);
}

