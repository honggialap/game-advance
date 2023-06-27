#pragma once
#ifndef __ENGINE__ACTOR__PLAYER_TANK_H__
#define __ENGINE__ACTOR__PLAYER_TANK_H__

#include "engine/core/game_object.h"

#include "engine/component/updatable.h"
#include "engine/component/physics.h"
#include "engine/component/commandable.h"
#include "engine/component/recordable.h"
#include "engine/component/resource_loadable.h"
#include "engine/component/animation.h"
#include "engine/component/renderable.h"
#include "engine/component/player_control.h"
#include "engine/component/team.h"
#include "engine/component/health.h"
#include "engine/component/movement.h"
#include "engine/component/input_handler.h"
#include "engine/component/remote_object.h"

namespace NSEngine {
	namespace NSActor {

		struct CPlayerTankRecord 
			: public NSCore::CRecord {
			float position_x, position_y;
			float velocity_x, velocity_y;
			int32_t movement_x, movement_y;

			CPlayerTankRecord(
				uint32_t id
			);

			CPlayerTankRecord(
				uint32_t id
				, float position_x, float position_y
				, float velocity_x, float velocity_y
				, int32_t movement_x, int32_t movement_y
			);
		};
		typedef CPlayerTankRecord* pPlayerTankRecord;

		struct CMoveCommand 
			: public NSCore::CCommand {
			int32_t x;
			int32_t y;

			CMoveCommand(
				uint32_t game_object_id,
				int32_t x,
				int32_t y
			) :
				CCommand(game_object_id),
				x(x),
				y(y)
			{
				command_type = ECommandType::PLAYER_TANK_MOVE;
			}
		};
		typedef CMoveCommand* pMoveCommand;

		struct CShootCommand
			: public NSCore::CCommand {
			CShootCommand(
				uint32_t game_object_id
			) :
				CCommand(game_object_id)
			{
				command_type = ECommandType::PLAYER_TANK_SHOOT;
			}
		};
		typedef CShootCommand* pShootCommand;

		class CPlayerTank
			: public NSCore::CGameObject
			, public NSComponent::CUpdatable
			, public NSComponent::CPhysics
			, public NSComponent::CCommandable
			, public NSComponent::CRecordable
			, public NSComponent::CResourceLoadable
			, public NSComponent::CAnimation
			, public NSComponent::CRenderable
			, public NSComponent::CTeam
			, public NSComponent::CHealth
			, public NSComponent::CPlayerControl 
			, public NSComponent::CMovement {
		public:
			CPlayerTank(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CPlayerTank();

			void LoadResource() override;
			void UnloadResource() override;

			void Serialize(uint32_t tick) override;
			void Deserialize(NSEngine::NSCore::pRecord record) override;

			void ExecuteCommand(NSEngine::NSCore::pCommand command) override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void PackRecord(
				NSEngine::NSNetworks::CPacket* packet
				, NSEngine::NSCore::pRecord record
			) override;

			NSEngine::NSCore::pRecord UnpackRecord(
				NSEngine::NSNetworks::CPacket* packet
			) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CPlayerTank* pPlayerTank;

	}
}

#endif // !__ENGINE__ACTOR__PLAYER_TANK_H__
