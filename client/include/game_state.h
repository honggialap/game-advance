#pragma once
#ifndef __CLIENT_GAME_STATE_H__
#define __CLIENT_GAME_STATE_H__

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

struct GameStates {
	std::map<uint32_t, std::vector<pGameState>> game_states_by_tick;

	bool emptry() {
		return game_states_by_tick.empty();
	}

	bool found(uint32_t tick) {
		return game_states_by_tick.find(tick) != game_states_by_tick.end();
	}

	void push(uint32_t tick, pGameState game_state) {
		game_states_by_tick[tick].push_back(
			std::move(game_state)
		);
	}
	
	std::vector<pGameState>& get(uint32_t tick) {
		return game_states_by_tick[tick];
	}

	void erase(uint32_t tick) {
		if (found(tick)) {
			game_states_by_tick[tick].clear();
			game_states_by_tick.erase(tick);
		}
	}

	void clear() {
		for (auto& game_states : game_states_by_tick) {
			game_states.second.clear();
		}
		game_states_by_tick.clear();
	}
};
typedef std::unique_ptr<GameStates> pGameStates;

#endif // !__CLIENT_GAME_STATE_H__
