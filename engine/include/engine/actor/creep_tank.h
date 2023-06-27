#pragma once
#ifndef __ENGINE__ACTOR__CREEP_TANK_H__
#define __ENGINE__ACTOR__CREEP_TANK_H__

#include "engine/core/game_object.h"

#include "engine/component/updatable.h"
#include "engine/component/physics.h"
#include "engine/component/commandable.h"
#include "engine/component/recordable.h"
#include "engine/component/resource_loadable.h"
#include "engine/component/animation.h"
#include "engine/component/renderable.h"
#include "engine/component/ai_control.h"
#include "engine/component/team.h"
#include "engine/component/health.h"
#include "engine/component/input_handler.h"
#include "engine/component/remote_object.h"

namespace NSEngine {
	namespace NSActor {

		struct CCreepTankRecord
			: public NSCore::CRecord {
			float position_x, position_y;
			float velocity_x, velocity_y;

			CCreepTankRecord(
				uint32_t id
			);

			CCreepTankRecord(
				uint32_t id
				, float position_x, float position_y
				, float velocity_x, float velocity_y
			);
		};
		typedef CCreepTankRecord* pCreepTankRecord;

		class CCreepTank
			: public NSCore::CGameObject
			, public NSComponent::CUpdatable
			, public NSComponent::CPhysics
			, public NSComponent::CCommandable
			, public NSComponent::CRecordable
			, public NSComponent::CResourceLoadable
			, public NSComponent::CAnimation
			, public NSComponent::CRenderable
			, public NSComponent::CAIControl
			, public NSComponent::CTeam
			, public NSComponent::CHealth {
		public:
			CCreepTank(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CCreepTank();

			void LoadResource() override;
			void UnloadResource() override;

			void Serialize(uint32_t tick) override;
			void Deserialize(NSCore::pRecord record) override;

			void PackRecord(
				NSNetworks::CPacket* packet
				, NSCore::pRecord record
			) override;

			NSCore::pRecord UnpackRecord(
				NSNetworks::CPacket* packet
			) override;

			void ExecuteCommand(NSCore::pCommand command) override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSComponent::pPhysics other) override;
			void OnCollisionExit(NSComponent::pPhysics other) override;

		};
		typedef CCreepTank* pCreepTank;

	}
}

#endif // !__ENGINE__ACTOR__CREEP_TANK_H__
