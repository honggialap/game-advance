#pragma once
#ifndef __SERVER__ACTOR__REPAIR_KIT_H__
#define __SERVER__ACTOR__REPAIR_KIT_H__

#include "engine/actor/repair_kit.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CRepairKit
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CRepairKit {
		public:
			static CRepairKit* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, nlohmann::json& data
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

#endif // !__SERVER__ACTOR__REPAIR_KIT_H__
