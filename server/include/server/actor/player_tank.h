#pragma once
#ifndef __SERVER__ACTOR__PLAYER_TANK_H__
#define __SERVER__ACTOR__PLAYER_TANK_H__

#include "engine/actor/player_tank.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CPlayerTank
			: public NSEngine::NSActor::CPlayerTank
			, public NSServer::NSCore::CGameObject {
		public:
			static CPlayerTank* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, nlohmann::json& data
			);

			CPlayerTank(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CPlayerTank();

			void Load(std::string data_path) override;
			void Unload() override;

			void HandleInput(uint32_t tick) override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CPlayerTank* pPlayerTank;

	}
}

#endif // !__SERVER__ACTOR__PLAYER_TANK_H__
