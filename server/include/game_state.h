#pragma once
#ifndef __SERVER_GAME_STATE_H__
#define __SERVER_GAME_STATE_H__

#include "common.h"

class GameState {
public:
	uint32_t tick;
};
typedef GameState* pGameState;

#endif // !__SERVER_GAME_STATE_H__
