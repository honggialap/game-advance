#pragma once
#ifndef __CLIENT__ACTOR__PLAYER_TANK_H__
#define __CLIENT__ACTOR__PLAYER_TANK_H__

#include "engine/actor/player_tank.h"
#include "engine/component/input_handler.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CPlayerTank
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CPlayerTank 
			, public NSEngine::NSComponent::CInputHandler {
		public:
			float last_known_x = 0;
			float last_known_y = 0;
			float latest_x = 0;
			float latest_y = 0;

			static CPlayerTank* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CPlayerTank(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CPlayerTank();

			void HandleInput(uint32_t tick) override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void SendMoveCommand(uint32_t tick, NSEngine::NSActor::CMoveCommand move_command);
		};
		typedef CPlayerTank* pPlayerTank;

	}
}

#endif // !__CLIENT__ACTOR__PLAYER_TANK_H__
