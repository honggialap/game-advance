#pragma once
#ifndef __SERVER__ACTOR__STEEL_H__
#define __SERVER__ACTOR__STEEL_H__

#include "server/core/game_object.h"
#include "engine/actor/terrain/steel.h"

namespace NSServer {
	namespace NSActor {

		class CSteel
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CSteel
		{
		public:
			static CSteel* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, nlohmann::json& components_data
			);

			CSteel(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CSteel();

		};
		typedef CSteel* pSteel;

	}
}

#endif // !__SERVER__ACTOR__STEEL_H__
