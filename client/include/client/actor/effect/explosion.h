#pragma once
#ifndef __CLIENT__ACTOR__EXPLOSION_H__
#define __CLIENT__ACTOR__EXPLOSION_H__

#include "client/core/game_object.h"
#include "engine/actor/effect/explosion.h"

namespace NSClient {
	namespace NSActor {

		class CExplosion
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CExplosion
		{
		public:
			static CExplosion* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CExplosion(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CExplosion();

		};
		typedef CExplosion* pExplosion;

	}
}

#endif // !__CLIENT__ACTOR__EXPLOSION_H__
