#pragma once
#ifndef __SERVER__ACTOR__WATER_H__
#define __SERVER__ACTOR__WATER_H__

#include "engine/actor/water.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CWater
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CWater {
		public:
			static CWater* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, nlohmann::json& components_data
			);

			CWater(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CWater();

		};
		typedef CWater* pWater;

	}
}

#endif // !__SERVER__ACTOR__WATER_H__
