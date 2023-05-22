#include "client_scene.h"
#include "game_client.h"

ClientScene::ClientScene(Game* game) 
	: Scene(game)
	, game_client(static_cast<GameClient*>(game)) {
}

ClientScene::~ClientScene() {
}