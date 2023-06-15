#pragma once
#ifndef __CLIENT__ACTOR__REPAIR_KIT_H__
#define __CLIENT__ACTOR__REPAIR_KIT_H__

#include "engine/actor/repair_kit.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CRepairKit
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CRepairKit {
		public:
			static CRepairKit* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CRepairKit(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CRepairKit();

		};
		typedef CRepairKit* pRepairKit;

	}
}

#endif // !__CLIENT__ACTOR__REPAIR_KIT_H__
