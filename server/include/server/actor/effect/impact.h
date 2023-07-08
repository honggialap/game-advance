#pragma once
#ifndef __SERVER__ACTOR__IMPACT_H__
#define __SERVER__ACTOR__IMPACT_H__

#include "server/core/game_object.h"
#include "engine/actor/effect/impact.h"

namespace NSServer {
	namespace NSActor {

		class CImpact
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CImpact
		{
		public:
			static CImpact* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, nlohmann::json& components_data
			);

			CImpact(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CImpact();

		};
		typedef CImpact* pImpact;

	}
}

#endif // !__SERVER__ACTOR__IMPACT_H__
