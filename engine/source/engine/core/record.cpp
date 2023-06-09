#include "engine/core/record.h"

namespace NSEngine {
	namespace NSCore {

		CRecord::CRecord(uint32_t game_object_id)
			: game_object_id(game_object_id)
			, actor_type(EActorType::INVALID_ACTOR) {
		}

		CRecord::~CRecord() {
		}

	}
}