#pragma once
#ifndef __ENGINE__ACTOR__BASIC_TANK_H__
#define __ENGINE__ACTOR__BASIC_TANK_H__

#include "engine/actor/tank/enemy_tank.h"
#include "engine/component/system/recordable.h"

namespace NSEngine {
	namespace NSActor {

		enum EBasicTankState : uint16_t {

		};

		struct CBasicTankRecord
			: public NSCore::CRecord {
			float position_x, position_y;
			float velocity_x, velocity_y;

			CBasicTankRecord(
				uint32_t id
			);

			CBasicTankRecord(
				uint32_t id
				, float position_x, float position_y
				, float velocity_x, float velocity_y
			);
		};
		typedef CBasicTankRecord* pBasicTankRecord;

		class CBasicTank
			: public NSActor::CEnemyTank
			, public NSComponent::CRecordable
		{
		protected:
			std::map<uint32_t, sf::Sprite> tank_sprites;

			EBasicTankState state;

		public:
			CBasicTank(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CBasicTank();

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
		typedef CBasicTank* pBasicTank;

	}
}

#endif // !__ENGINE__ACTOR__BASIC_TANK_H__
