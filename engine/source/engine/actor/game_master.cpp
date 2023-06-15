#include "engine/actor/game_master.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CGameMasterRecord::CGameMasterRecord(
			uint32_t id
		)
			: NSCore::CRecord(id) 
			, a(0.0f) {
			actor_type = EActorType::GAME_MASTER;
		}

		CGameMasterRecord::CGameMasterRecord(
			uint32_t id
			, float a
		)
			: NSCore::CRecord(id) 
			, a(a) {
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
					id
				)
			);
		}

		void CGameMaster::Deserialize(NSCore::pRecord record) {
			auto game_master_record = static_cast<pGameMasterRecord>(record);
		}

		void CGameMaster::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto game_master_record = static_cast<pGameMasterRecord>(record);
			//*packet << factory_record->a;
		}

		NSCore::pRecord CGameMaster::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CGameMasterRecord(id);

			//*packet >> factory_record->a;

			return record;
		}

		void CGameMaster::Update(float elapsed) {
		}

		void CGameMaster::PackNetworksLoadPacket(NSNetworks::CPacket* packet) {
		}

		void CGameMaster::UnpackNetworksLoadPacket(NSNetworks::CPacket* packet) {
		}

	}
}