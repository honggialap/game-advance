#pragma once
#ifndef __ENGINE__ACTOR__TANK_H__
#define __ENGINE__ACTOR__TANK_H__

#include "engine/actor/power_up/base_power_up.h"
#include "engine/component/system/recordable.h"

namespace NSEngine {
	namespace NSActor {

		struct CTankRecord
			: public NSCore::CRecord {
			CTankRecord(uint32_t id);
		};
		typedef CTankRecord* pTankRecord;

		class CTank
			: public NSActor::CBasePowerUp
			, public NSComponent::CRecordable
		{
		public:
			CTank(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CTank();

			void Serialize(uint32_t tick) override;
			void Deserialize(NSCore::pRecord record) override;

			void PackRecord(NSNetworks::CPacket* packet, NSCore::pRecord record) override;
			NSCore::pRecord UnpackRecord(NSNetworks::CPacket* packet) override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSComponent::pPhysics other) override;
			void OnCollisionExit(NSComponent::pPhysics other) override;
		};
		typedef CTank* pTank;

	}
}

#endif // !__ENGINE__ACTOR__TANK_H__
