#pragma once
#ifndef __SERVER_GAME_STATE_H__
#define __SERVER_GAME_STATE_H__

#include "common.h"

struct GameState {
	uint32_t id;
	uint32_t type;

	float position_x;
	float position_y;

	float velocity_x;
	float velocity_y;

	GameState(
		uint32_t id,
		uint32_t type,
		float position_x,
		float position_y,
		float velocity_x,
		float velocity_y
	) :
		id(id),
		type(type),
		position_x(position_x),
		position_y(position_y),
		velocity_x(velocity_x),
		velocity_y(velocity_y)
	{}
};
typedef std::unique_ptr<GameState> pGameState;

#endif // !__SERVER_GAME_STATE_H__
