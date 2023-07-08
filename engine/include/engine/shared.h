#pragma once
#ifndef __ENGINE__SHARED_H__
#define __ENGINE__SHARED_H__

#include "engine/common.h"

namespace NSEngine {

	enum EPacketType
		: uint16_t {
		INVALID					=	0,
									
		WELCOME					=	1001,
		NOT_WELCOME				=	1002,
									
		PLAYER_PICK				=	2001,
		PLAYER_LOCK				=	2002,
		PLAYER_CONFIRM			=	2003,
		PLAY_NEXT_SCENE			=	2004,
									
		CLIENT_READY			=	3001,
		SERVER_LOAD				=	3002,
		CLIENT_LOAD				=	3003,
		START_GAME				=	3004,
									
		PING					=	4001,
		SERVER_GAME_STATE		=	4002,
									
		PLAYER_MOVE				=	5001,
		PLAYER_SHOOT			=	5002,
	};

	enum ESceneType
		: uint32_t {
		INVALID_SCENE			=	0,

		LOBBY_SCENE				=	1001,
		MAIN_SCENE				=	1002,
	};

	enum EActorType
		: uint32_t {
		INVALID_ACTOR	=	0,

		GAME_MASTER		=	1001,
		HEADQUARTER		=	2001,

		PLAYER_TANK		=	3011,
		BASIC_TANK		=	3012,
		FAST_TANK		=	3013,
		POWER_TANK		=	3014,
		ARMOR_TANK		=	3015,
		BULLET			=	3021,

		GRENADE			=	4001,
		HELMET			=	4002,
		SHOVEL			=	4003,
		STAR			=	4004,
		TANK			=	4005,
		TIMER			=	4006,

		BOUND			=	5001,
		BRICK			=	5002,
		STEEL			=	5003,
		TREE			=	5004,
		WATER			=	5005,
		ICE				=	5006,

		SCORE			=	6001,
		IMPACT			=	6002,
		EXPLOSION		=	6003
	};

	enum ECommandType 
		: uint32_t {
		INVALID_COMMAND			=	0,

		TANK_MOVE				=	1001,
		TANK_SHOOT				=	1002
	};

	enum ECollisionFilter 
		: uint16_t {
		FILTER_NON_COLLIDABLE			=	0x0001,
		FILTER_PLAYER_TANK				=	0x0002,
		FILTER_CREEP_TANK				=	0x0004,
		FILTER_BULLET					=	0x0008,
		FILTER_STRUCTURE				=	0x0010,
		FILTER_WALL						=	0x0020,
		FILTER_WATER					=	0x0040,
		FILTER_TREE						=	0x0080,
		FILTER_PICK_UP					=	0x0100,
	};

	enum ETeam : uint32_t {
		INVALID_TEAM = 0,

		PLAYER = 1001,
		AI = 1002,
	};

}

#endif // !__ENGINE__SHARED_H__
