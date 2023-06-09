#pragma once
#ifndef __SERVER__ACTOR__TURRET_BULLET_H__
#define __SERVER__ACTOR__TURRET_BULLET_H__

#include "engine/actor/turret_bullet.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CTurretBullet
			: public NSEngine::NSActor::CTurretBullet
			, public NSServer::NSCore::CGameObject {
		public:
			static CTurretBullet* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, std::string data_path
			);

			CTurretBullet(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
			);
			~CTurretBullet();

			void Load(std::string data_path) override;
			void Unload() override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CTurretBullet* pTurretBullet;

	}
}

#endif // !__SERVER__ACTOR__TURRET_BULLET_H__
