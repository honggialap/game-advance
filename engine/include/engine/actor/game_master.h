#pragma once
#ifndef __ENGINE__ACTOR__GAME_MASTER_H__
#define __ENGINE__ACTOR__GAME_MASTER_H__

#include "engine/core/game_object.h"

#include "engine/component/loadable.h"
#include "engine/component/updatable.h"
#include "engine/component/recordable.h"

namespace NSEngine {
	namespace NSActor {

		struct CGameMasterRecord 
			: public NSEngine::NSCore::CRecord {
			CGameMasterRecord(uint32_t id);
		};
		typedef CGameMasterRecord* pGameMasterRecord;

		class CGameMaster
			: public NSEngine::NSCore::CGameObject
			, public NSEngine::NSComponent::CLoadable
			, public NSEngine::NSComponent::CUpdatable
			, public NSEngine::NSComponent::CRecordable {
		public:
			CGameMaster(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CGameMaster();

			void Load(std::string data_path) override;
			void Unload() override;

			void Serialize(uint32_t tick) override;
			void Deserialize(NSEngine::NSCore::pRecord record) override;

			void Update(float elapsed) override;
		};
		typedef CGameMaster* pGameMaster;

	}
}

#endif // !__ENGINE__ACTOR__GAME_MASTER_H__
