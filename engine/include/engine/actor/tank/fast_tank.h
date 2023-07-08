#pragma once
#ifndef __ENGINE__ACTOR__FAST_TANK_H__
#define __ENGINE__ACTOR__FAST_TANK_H__

#include "engine/actor/tank/enemy_tank.h"
#include "engine/component/system/recordable.h"

namespace NSEngine {
	namespace NSActor {

		struct CFastTankRecord
			: public NSCore::CRecord 
		{
			float position_x, position_y;
			float velocity_x, velocity_y;
			int32_t movement_x, movement_y;

			CFastTankRecord(
				uint32_t id
			);

			CFastTankRecord(
				uint32_t id
				, float position_x, float position_y
				, float velocity_x, float velocity_y
				, int32_t movement_x, int32_t movement_y
			);
		};
		typedef CFastTankRecord* pFastTankRecord;

		class CFastTank
			: public NSActor::CEnemyTank
			, public NSComponent::CRecordable
		{
		protected:
			std::map<uint32_t, sf::Sprite> tank_sprites;

		public:
			CFastTank(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CFastTank();

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
		typedef CFastTank* pFastTank;

	}
}

#endif // !__ENGINE__ACTOR__FAST_TANK_H__
