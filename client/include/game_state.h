#pragma once
#ifndef __CLIENT_GAME_STATE_H__
#define __CLIENT_GAME_STATE_H__

#include "common.h"

struct GameObjectState {
	float position_x;
	float position_y;

	float velocity_x;
	float velocity_y;
};

class GameState {
public:
	uint32_t tick;
	std::map<uint32_t, GameObjectState> game_object_states;
};


#endif // !__CLIENT_GAME_STATE_H__
