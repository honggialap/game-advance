#pragma once
#ifndef __CLIENT__CLIENT_WORLD_H__
#define __CLIENT__CLIENT_WORLD_H__

#include "game_client.h"
#include "world.h"

class ClientWorld : public World {
protected:
	GameClient* game_client;

public:
	ClientWorld(Game* game);
	~ClientWorld();
};

#endif // !__CLIENT__CLIENT_WORLD_H__
