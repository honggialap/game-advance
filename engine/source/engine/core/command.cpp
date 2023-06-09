#include "engine/core/command.h"

namespace NSEngine {
	namespace NSCore {

		CCommand::CCommand(uint32_t game_object_id)
			: game_object_id(game_object_id)
			, command_type(ECommandType::INVALID_COMMAND) {
		}

		CCommand::~CCommand() {
		}

	}
}