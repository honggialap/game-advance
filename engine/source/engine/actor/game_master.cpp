#include "engine/actor/game_master.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CGameMasterRecord::CGameMasterRecord(
			uint32_t id
		)
			: NSEngine::NSCore::CRecord(id) 
			, a(0.0f) {
			actor_type = EActorType::GAME_MASTER;
		}

		CGameMasterRecord::CGameMasterRecord(
			uint32_t id
			, float a
		)
			: NSEngine::NSCore::CRecord(id) 
			, a(a) {
			actor_type = EActorType::GAME_MASTER;
		}

		CGameMaster::CGameMaster(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSCore::CGameObject(game, world, id, name) {
			type = EActorType::GAME_MASTER;
		}

		CGameMaster::~CGameMaster() {
		}

		void CGameMaster::Load(std::string data_path) {
			//std::ifstream data_file(data_path);
			//nlohmann::json data = nlohmann::json::parse(data_file);

		}

		void CGameMaster::Unload() {
		}

		void CGameMaster::PackLoad(NSEngine::NSNetworks::CPacket* packet) {
		}

		void CGameMaster::UnpackLoad(NSEngine::NSNetworks::CPacket* packet) {
		}

		void CGameMaster::Serialize(uint32_t tick) {
			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CGameMasterRecord>(
					id
				)
			);
		}

		void CGameMaster::Deserialize(NSEngine::NSCore::pRecord record) {
			auto game_master_record = static_cast<pGameMasterRecord>(record);
		}

		void CGameMaster::PackRecord(
			NSEngine::NSNetworks::CPacket* packet
			, NSEngine::NSCore::pRecord record
		) {
			auto game_master_record = static_cast<pGameMasterRecord>(record);
			//*packet << factory_record->a;
		}

		void CGameMaster::UnpackRecord(
			NSEngine::NSNetworks::CPacket* packet
			, NSEngine::NSCore::pRecord record
		) {
			auto game_master_record = static_cast<pGameMasterRecord>(record);
			//*packet >> factory_record->a;
		}

		void CGameMaster::Update(float elapsed) {
		}

	}
}