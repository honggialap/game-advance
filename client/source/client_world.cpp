#include "client_world.h"

ClientWorld::ClientWorld(Game* game)
	: World(game)
	, game_client(static_cast<GameClient*>(game))
{}

ClientWorld::~ClientWorld() {
}
