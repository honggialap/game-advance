#pragma once
#ifndef __CLIENT__ACTOR__PLAYER_BULLET_H__
#define __CLIENT__ACTOR__PLAYER_BULLET_H__

#include "engine/actor/player_bullet.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CPlayerBullet
			: public NSEngine::NSActor::CPlayerBullet
			, public NSClient::NSCore::CGameObject {
		public:
			static CPlayerBullet* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CPlayerBullet(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CPlayerBullet();

			void Load(std::string data_path) override;
			void Unload() override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CPlayerBullet* pPlayerBullet;

	}
}

#endif // !__CLIENT__ACTOR__PLAYER_BULLET_H__
