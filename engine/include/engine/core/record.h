#pragma once
#ifndef __ENGINE__CORE__RECORD_H__
#define __ENGINE__CORE__RECORD_H__

#include "engine/common.h"
#include "engine/shared.h"

namespace NSEngine {
	namespace NSCore {

		struct CRecord {
			uint32_t game_object_id;
			EActorType actor_type;

			CRecord(uint32_t game_object_id);
			virtual ~CRecord() = 0;
		};
		typedef CRecord* pRecord;
		typedef std::unique_ptr<CRecord> upRecord;

	}
}

#endif // !__ENGINE__CORE__RECORD_H__
