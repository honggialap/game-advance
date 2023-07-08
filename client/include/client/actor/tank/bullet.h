#pragma once
#ifndef __CLIENT__ACTOR__BULLET_H__
#define __CLIENT__ACTOR__BULLET_H__

#include "client/core/game_object.h"
#include "engine/actor/tank/bullet.h"

#include "engine/component/render/remote.h"

namespace NSClient {
	namespace NSActor {

		class CBullet
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CBullet

			, public NSEngine::NSComponent::CRemote
		{
		public:
			static CBullet* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
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

#endif // !__CLIENT__ACTOR__BULLET_H__
