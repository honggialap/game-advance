#pragma once
#ifndef __CLIENT__CLIENT_GAME_OBJECT_H__
#define __CLIENT__CLIENT_GAME_OBJECT_H__

#include "game_object.h"

#include "game_client.h"
#include "client_world.h"

class ClientGameObject : public GameObject {
protected:
	GameClient*		game_client		= nullptr;
	ClientWorld*	client_world	= nullptr;

public:
	ClientGameObject(Game* game, World* world);
	virtual ~ClientGameObject() = 0;
};

#endif // !__CLIENT__CLIENT_GAME_OBJECT_H__
