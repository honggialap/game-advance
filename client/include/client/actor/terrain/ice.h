#pragma once
#ifndef __CLIENT__ACTOR__ICE_H__
#define __CLIENT__ACTOR__ICE_H__

#include "client/core/game_object.h"
#include "engine/actor/terrain/ice.h"

namespace NSClient {
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

#endif // !__CLIENT__ACTOR__ICE_H__
