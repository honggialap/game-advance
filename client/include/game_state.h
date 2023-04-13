#pragma once
#ifndef __CLIENT_GAME_STATE_H__
#define __CLIENT_GAME_STATE_H__

#include "common.h"
#include "game_object.h"

class GameState {
public:
	std::map<uint32_t, GameObjectState> game_object;
};


#endif // !__CLIENT_GAME_STATE_H__
