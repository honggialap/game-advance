#pragma once
#ifndef __CLIENT_COMMAND_H__
#define __CLIENT_COMMAND_H__

#include "common.h"

class Command {
public:
	enum CommandType : uint32_t {
		Invalid,
		MoveCommand,
	};
	CommandType command_type;
	uint32_t tick;

	Command(uint32_t tick) : 
		tick(tick), 
		command_type(CommandType::Invalid) 
	{}
};
typedef Command* pCommand;

class MoveCommand : public Command {
public:
	uint32_t networks_id;
	int32_t vertical;
	int32_t horizontal;

	MoveCommand(uint32_t tick, uint32_t networks_id, int32_t vertical, int32_t horizontal) :
		Command(tick),
		networks_id(networks_id),
		vertical(vertical),
		horizontal(horizontal)
	{
		command_type = CommandType::MoveCommand;
	}
};
typedef MoveCommand* pMoveCommand;

#endif // !__CLIENT_COMMAND_H__
