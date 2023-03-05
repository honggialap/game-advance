#include "SampleLobbyScene.h"

SampleLobbyScene::SampleLobbyScene(pGame game) : Scene(game) {
	sample_game = static_cast<pSampleGame>(game);
}

SampleLobbyScene::~SampleLobbyScene() {
}

void SampleLobbyScene::Load(std::string data_path) {
}

void SampleLobbyScene::Unload() {
}

void SampleLobbyScene::Update(float elapsed) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {
		game->PlayScene(1);
	}
}

void SampleLobbyScene::Render(sf::RenderWindow& window) {
}

pGameObject SampleLobbyScene::CreateGameObject() {
	return pGameObject();
}
