#pragma once
#ifndef __SERVER__ACTOR__BULLET_H__
#define __SERVER__ACTOR__BULLET_H__

#include "server/core/game_object.h"
#include "engine/actor/tank/bullet.h"

namespace NSServer {
	namespace NSActor {

		class CBullet
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CBullet
		{
		public:
			static CBullet* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, nlohmann::json& components_data
			);

			CBullet(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CBullet();

		};
		typedef CBullet* pBullet;

	}
}

#endif // !__SERVER__ACTOR__BULLET_H__
