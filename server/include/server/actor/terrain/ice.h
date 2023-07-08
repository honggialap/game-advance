#pragma once
#ifndef __SERVER__ACTOR__ICE_H__
#define __SERVER__ACTOR__ICE_H__

#include "server/core/game_object.h"
#include "engine/actor/terrain/ice.h"

namespace NSServer {
	namespace NSActor {

		class CIce
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CIce
		{
		public:
			static CIce* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, nlohmann::json& components_data
			);

			CIce(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CIce();

		};
		typedef CIce* pIce;

	}
}

#endif // !__SERVER__ACTOR__ICE_H__
