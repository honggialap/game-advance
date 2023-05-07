#pragma once
#ifndef __SERVER_COMMAND_H__
#define __SERVER_COMMAND_H__

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

#endif // !__SERVER_COMMAND_H__
