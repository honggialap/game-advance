#pragma once
#ifndef __ENGINE__ACTOR__GAME_MASTER_H__
#define __ENGINE__ACTOR__GAME_MASTER_H__

#include "engine/core/game_object.h"

#include "engine/component/networks_loadable.h"
#include "engine/component/updatable.h"
#include "engine/component/recordable.h"
#include "engine/component/pooler.h"

namespace NSEngine {
	namespace NSActor {

		struct CGameMasterRecord 
			: public NSCore::CRecord {
			float a = 0.0f;
			
			CGameMasterRecord(
				uint32_t id
			);

			CGameMasterRecord(
				uint32_t id
				, float a
			);
		};
		typedef CGameMasterRecord* pGameMasterRecord;

		class CGameMaster
			: public NSCore::CGameObject
			, public NSComponent::CNetworksLoadable
			, public NSComponent::CUpdatable
			, public NSComponent::CRecordable
			, public NSComponent::CPooler {
		public:
			CGameMaster(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CGameMaster();

			void Serialize(uint32_t tick) override;
			void Deserialize(NSCore::pRecord record) override;

			void PackRecord(
				NSNetworks::CPacket* packet
				, NSCore::pRecord record
			) override;

			NSCore::pRecord UnpackRecord(
				NSNetworks::CPacket* packet
			) override;

			void Update(float elapsed) override;

			void PackNetworksLoadPacket(NSNetworks::CPacket* packet) override;
			void UnpackNetworksLoadPacket(NSNetworks::CPacket* packet) override;
		};
		typedef CGameMaster* pGameMaster;

	}
}

#endif // !__ENGINE__ACTOR__GAME_MASTER_H__
