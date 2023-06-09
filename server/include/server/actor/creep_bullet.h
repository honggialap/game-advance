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
				, std::string data_path
			);

			CCreepBullet(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
			);
			~CCreepBullet();

			void Load(std::string data_path) override;
			void Unload() override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CCreepBullet* pCreepBullet;
	
	}
}

#endif // !__SERVER__ACTOR__CREEP_BULLET_H__
