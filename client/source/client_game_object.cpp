#include "client_game_object.h"

ClientGameObject::ClientGameObject(Game* game, World* world)
	: GameObject(game, world)
	, game_client(static_cast<GameClient*>(game))
	, client_world(static_cast<ClientWorld*>(world))
{}

ClientGameObject::~ClientGameObject() {
}
