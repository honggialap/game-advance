#pragma once
#ifndef __SERVER__ACTOR__TURRET_BULLET_H__
#define __SERVER__ACTOR__TURRET_BULLET_H__

#include "engine/actor/turret_bullet.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CTurretBullet
			: public NSCore::CGameObject 
			, public NSEngine::NSActor::CTurretBullet {
		public:
			static CTurretBullet* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, nlohmann::json& data
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

#endif // !__SERVER__ACTOR__TURRET_BULLET_H__
