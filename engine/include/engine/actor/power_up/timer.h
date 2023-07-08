#pragma once
#ifndef __ENGINE__ACTOR__TIMER_H__
#define __ENGINE__ACTOR__TIMER_H__

#include "engine/actor/power_up/base_power_up.h"
#include "engine/component/system/recordable.h"

namespace NSEngine {
	namespace NSActor {

		struct CTimerRecord
			: public NSCore::CRecord {
			CTimerRecord(uint32_t id);
		};
		typedef CTimerRecord* pTimerRecord;

		class CTimer
			: public NSActor::CBasePowerUp
			, public NSComponent::CRecordable
		{
		public:
			CTimer(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CTimer();

			void Serialize(uint32_t tick) override;
			void Deserialize(NSCore::pRecord record) override;

			void PackRecord(NSNetworks::CPacket* packet, NSCore::pRecord record) override;
			NSCore::pRecord UnpackRecord(NSNetworks::CPacket* packet) override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSComponent::pPhysics other) override;
			void OnCollisionExit(NSComponent::pPhysics other) override;
		};
		typedef CTimer* pTimer;

	}
}

#endif // !__ENGINE__ACTOR__TIMER_H__
