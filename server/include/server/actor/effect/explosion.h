#pragma once
#ifndef __SERVER__ACTOR__EXPLOSION_H__
#define __SERVER__ACTOR__EXPLOSION_H__

#include "server/core/game_object.h"
#include "engine/actor/effect/explosion.h"

namespace NSServer {
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
				, nlohmann::json& components_data
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

#endif // !__SERVER__ACTOR__EXPLOSION_H__
