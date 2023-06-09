#pragma once
#ifndef __ENGINE__CORE__COMMAND_H__
#define __ENGINE__CORE__COMMAND_H__

#include "engine/common.h"
#include "engine/shared.h"

namespace NSEngine {
	namespace NSCore {

		struct CCommand {
			uint32_t game_object_id;
			ECommandType command_type;

			CCommand(uint32_t game_object_id);
			virtual ~CCommand() = 0;
		};
		typedef CCommand* pCommand;
		typedef std::unique_ptr<CCommand> upCommand;

	}
}

#endif // !__ENGINE__CORE__COMMAND_H__
