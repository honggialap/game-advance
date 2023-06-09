#pragma once
#ifndef __CLIENT__ACTOR__PLAYER_TANK_H__
#define __CLIENT__ACTOR__PLAYER_TANK_H__

#include "engine/actor/player_tank.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CPlayerTank
			: public NSEngine::NSActor::CPlayerTank
			, public NSClient::NSCore::CGameObject {
		public:
			float last_known_x = 0;
			float last_known_y = 0;
			float latest_x = 0;
			float latest_y = 0;

			static CPlayerTank* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, std::string data_path
			);

			CPlayerTank(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
			);
			~CPlayerTank();

			void Load(std::string data_path) override;
			void Unload() override;

			void HandleInput(uint32_t tick) override;
			void ExecuteCommand(NSEngine::NSCore::pCommand command) override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;

			void SendMoveCommand(uint32_t tick, NSEngine::NSActor::CMoveCommand move_command);
		};
		typedef CPlayerTank* pPlayerTank;

	}
}

#endif // !__CLIENT__ACTOR__PLAYER_TANK_H__
