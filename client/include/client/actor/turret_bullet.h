#pragma once
#ifndef __CLIENT__ACTOR__TURRET_BULLET_H__
#define __CLIENT__ACTOR__TURRET_BULLET_H__

#include "engine/actor/turret_bullet.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CTurretBullet
			: public NSEngine::NSActor::CTurretBullet
			, public NSClient::NSCore::CGameObject {
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
				, uint32_t id
				, std::string name
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

#endif // !__CLIENT__ACTOR__TURRET_BULLET_H__
