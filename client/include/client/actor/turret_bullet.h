#pragma once
#ifndef __CLIENT__ACTOR__TURRET_BULLET_H__
#define __CLIENT__ACTOR__TURRET_BULLET_H__

#include "engine/actor/turret_bullet.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CTurretBullet
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CTurretBullet {
		public:
			static CTurretBullet* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CTurretBullet(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CTurretBullet();

		};
		typedef CTurretBullet* pTurretBullet;

	}
}

#endif // !__CLIENT__ACTOR__TURRET_BULLET_H__
