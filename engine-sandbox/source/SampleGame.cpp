#include "SampleGame.h"
#include "SampleLobbyScene.h"
#include "SampleWorldScene.h"

pScene SampleGame::CreateScene(unsigned int scene_type) {
	switch (scene_type) {
	case SCENE_ID_LOBBY:
		return new SampleLobbyScene(this);
		break;

	case SCENE_ID_WORLD:
		return new SampleWorldScene(this);
		break;

	default:
		return nullptr;
		break;
	}
}

void SampleGame::Initialize(std::string data_path) {
	Game::Initialize(data_path);
	// for additional stuff, if have any

}

void SampleGame::Shutdown() {

	// for additional stuff, if have any
	Game::Shutdown();
}
