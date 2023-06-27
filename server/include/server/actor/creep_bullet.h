#pragma once
#ifndef __SERVER__ACTOR__CREEP_BULLET_H__
#define __SERVER__ACTOR__CREEP_BULLET_H__

#include "engine/actor/creep_bullet.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CCreepBullet
			: public NSEngine::NSActor::CCreepBullet
			, public NSServer::NSCore::CGameObject {
		public:
			static CCreepBullet* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, nlohmann::json& components_data
			);

			CCreepBullet(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CCreepBullet();

		};
		typedef CCreepBullet* pCreepBullet;
	
	}
}

#endif // !__SERVER__ACTOR__CREEP_BULLET_H__
