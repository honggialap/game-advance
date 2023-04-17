#pragma once
#ifndef __CLIENT_COMMAND_H__
#define __CLIENT_COMMAND_H__

#include "common.h"

class Command {
public:
	enum Type : uint32_t {
		Invalid,
		Move,
	};
	Type type;
	uint32_t tick;

	Command(uint32_t tick) : 
		tick(tick), 
		type(Type::Invalid) 
	{}
};
typedef Command* pCommand;

class MoveCommand : public Command {
public:
	uint32_t id;
	int32_t x;
	int32_t y;

	MoveCommand(uint32_t tick, uint32_t id, int32_t x, int32_t y) :
		Command(tick),
		id(id),
		x(x),
		y(y)
	{
		type = Type::Move;
	}
};
typedef MoveCommand* pMoveCommand;

#endif // !__CLIENT_COMMAND_H__
