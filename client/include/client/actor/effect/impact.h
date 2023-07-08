#pragma once
#ifndef __CLIENT__ACTOR__IMPACT_H__
#define __CLIENT__ACTOR__IMPACT_H__

#include "client/core/game_object.h"
#include "engine/actor/effect/impact.h"

namespace NSClient {
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

#endif // !__CLIENT__ACTOR__IMPACT_H__
