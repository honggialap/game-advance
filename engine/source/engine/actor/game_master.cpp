#include "engine/actor/game_master.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CGameMasterRecord::CGameMasterRecord(
			uint32_t id
		)
			: NSCore::CRecord(id) 
			, match_time(0.0f) {
			actor_type = EActorType::GAME_MASTER;
		}

		CGameMasterRecord::CGameMasterRecord(
			uint32_t id
			, float match_time
		)
			: NSCore::CRecord(id) 
			, match_time(match_time) {
			actor_type = EActorType::GAME_MASTER;
		}

		CGameMaster::CGameMaster(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world, id, name) {
			type = EActorType::GAME_MASTER;
		}

		CGameMaster::~CGameMaster() {
		}

		void CGameMaster::Serialize(uint32_t tick) {
			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CGameMasterRecord>(
					id, match_time
				)
			);
		}

		void CGameMaster::Deserialize(NSCore::pRecord record) {
			auto game_master_record = static_cast<pGameMasterRecord>(record);
			SetMatchTime(game_master_record->match_time);
		}

		void CGameMaster::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto game_master_record = static_cast<pGameMasterRecord>(record);
			*packet << game_master_record->match_time;
		}

		NSCore::pRecord CGameMaster::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CGameMasterRecord(id);
			*packet >> record->match_time;

			return record;
		}

		void CGameMaster::Update(float elapsed) {
		}

	}
}