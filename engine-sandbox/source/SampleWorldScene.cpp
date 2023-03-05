#include "SampleWorldScene.h"
#include "SampleGameObject.h"

SampleWorldScene::SampleWorldScene(pGame game) : Scene(game) {
	sample_game = static_cast<pSampleGame>(game);
}

SampleWorldScene::~SampleWorldScene() {
}

void SampleWorldScene::Load(std::string data_path) {
	camera.reset(sf::FloatRect(0, 0, 800, 600));

	game_object.reset(new SampleGameObject(game, this));
	game_object->Load();
}

void SampleWorldScene::Unload() {
	game_object->Unload();
	game_object.reset();
}

void SampleWorldScene::Update(float elapsed) {
	game_object->Update(elapsed);
}

void SampleWorldScene::Render(sf::RenderWindow& window) {
	window.setView(camera);
	game_object->Render(window);
}

pGameObject SampleWorldScene::CreateGameObject() {
	return pGameObject();
}

sf::View& SampleWorldScene::GetCamera() {
	return camera;
}
