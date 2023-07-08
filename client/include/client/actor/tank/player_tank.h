#pragma once
#ifndef __CLIENT__ACTOR__PLAYER_TANK_H__
#define __CLIENT__ACTOR__PLAYER_TANK_H__

#include "client/core/game_object.h"
#include "engine/actor/tank/player_tank.h"

#include "engine/component/system/input_handler.h"

#include "engine/component/render/remote.h"

namespace NSClient {
	namespace NSActor {

		class CPlayerTank
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CPlayerTank

			, public NSEngine::NSComponent::CInputHandler

			, public NSEngine::NSComponent::CRemote
		{
		public:
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
			void SendShootCommand(uint32_t tick, NSEngine::NSActor::CShootCommand shoot_command);

			void UnpackLoadPacket(NSEngine::NSNetworks::CPacket* packet) override;
		};
		typedef CPlayerTank* pPlayerTank;

	}
}

#endif // !__CLIENT__ACTOR__PLAYER_TANK_H__
