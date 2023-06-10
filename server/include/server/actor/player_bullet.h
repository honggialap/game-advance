#pragma once
#ifndef __SERVER__ACTOR__PLAYER_BULLET_H__
#define __SERVER__ACTOR__PLAYER_BULLET_H__

#include "engine/actor/player_bullet.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CPlayerBullet
			: public NSEngine::NSActor::CPlayerBullet
			, public NSServer::NSCore::CGameObject {
		public:
			static CPlayerBullet* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, nlohmann::json& data
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

#endif // !__SERVER__ACTOR__PLAYER_BULLET_H__
