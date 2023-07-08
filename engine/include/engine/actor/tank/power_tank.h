#pragma once
#ifndef __ENGINE__ACTOR__POWER_TANK_H__
#define __ENGINE__ACTOR__POWER_TANK_H__

#include "engine/actor/tank/enemy_tank.h"
#include "engine/component/system/recordable.h"

namespace NSEngine {
	namespace NSActor {

		struct CPowerTankRecord
			: public NSCore::CRecord
		{
			float position_x, position_y;
			float velocity_x, velocity_y;
			int32_t movement_x, movement_y;

			CPowerTankRecord(
				uint32_t id
			);

			CPowerTankRecord(
				uint32_t id
				, float position_x, float position_y
				, float velocity_x, float velocity_y
				, int32_t movement_x, int32_t movement_y
			);
		};
		typedef CPowerTankRecord* pPowerTankRecord;

		class CPowerTank
			: public NSActor::CEnemyTank
			, public NSComponent::CRecordable
		{
		protected:
			std::map<uint32_t, sf::Sprite> tank_sprites;

		public:
			CPowerTank(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CPowerTank();

			void LoadResource() override;
			void UnloadResource() override;

			void Serialize(uint32_t tick) override;
			void Deserialize(NSCore::pRecord record) override;

			void ExecuteCommand(NSCore::pCommand command) override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void PackRecord(
				NSNetworks::CPacket* packet
				, NSCore::pRecord record
			) override;

			NSCore::pRecord UnpackRecord(
				NSNetworks::CPacket* packet
			) override;

			void OnCollisionEnter(NSComponent::pPhysics other) override;
			void OnCollisionExit(NSComponent::pPhysics other) override;
		};
		typedef CPowerTank* pPowerTank;

	}
}

#endif // !__ENGINE__ACTOR__POWER_TANK_H__
