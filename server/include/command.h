#pragma once
#ifndef __SERVER_COMMAND_H__
#define __SERVER_COMMAND_H__

#include "common.h"

#include "common.h"

struct Command {
	uint32_t game_object_id;
	uint32_t command_type;

	Command(uint32_t game_object_id) :
		game_object_id(game_object_id),
		command_type(0)
	{}
};
typedef std::unique_ptr<Command> pCommand;

struct Commands {
	std::map<uint32_t, std::vector<pCommand>> commands_by_tick;

	bool empty() {
		return commands_by_tick.empty();
	}

	bool found(uint32_t tick) {
		return (commands_by_tick.find(tick) != commands_by_tick.end());
	}

	void push(uint32_t tick, pCommand command) {
		commands_by_tick[tick].push_back(
			std::move(command)
		);
	}

	std::vector<pCommand>& get(uint32_t tick) {
		return commands_by_tick[tick];
	}

	void erase(uint32_t tick) {
		if (found(tick)) {
			commands_by_tick[tick].clear();
			commands_by_tick.erase(tick);
		}
	}

	void clear(uint32_t tick) {
		for (auto& commands : commands_by_tick) {
			commands.second.clear();
		}
		commands_by_tick.clear();
	}

};
typedef std::unique_ptr<Commands> pCommands;

#endif // !__SERVER_COMMAND_H__
