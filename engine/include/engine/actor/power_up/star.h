#pragma once
#ifndef __ENGINE__ACTOR__STAR_H__
#define __ENGINE__ACTOR__STAR_H__

#include "engine/actor/power_up/base_power_up.h"
#include "engine/component/system/recordable.h"

namespace NSEngine {
	namespace NSActor {

		struct CStarRecord
			: public NSCore::CRecord {
			CStarRecord(uint32_t id);
		};
		typedef CStarRecord* pStarRecord;

		class CStar
			: public NSActor::CBasePowerUp
			, public NSComponent::CRecordable
		{
		public:
			CStar(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CStar();

			void Serialize(uint32_t tick) override;
			void Deserialize(NSCore::pRecord record) override;

			void PackRecord(NSNetworks::CPacket* packet, NSCore::pRecord record) override;
			NSCore::pRecord UnpackRecord(NSNetworks::CPacket* packet) override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSComponent::pPhysics other) override;
			void OnCollisionExit(NSComponent::pPhysics other) override;
		};
		typedef CStar* pStar;

	}
}

#endif // !__ENGINE__ACTOR__STAR_H__
