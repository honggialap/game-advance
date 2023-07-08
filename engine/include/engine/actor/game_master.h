#pragma once
#ifndef __ENGINE__ACTOR__GAME_MASTER_H__
#define __ENGINE__ACTOR__GAME_MASTER_H__

#include "engine/core/game_object.h"

#include "engine/component/system/updatable.h"
#include "engine/component/system/recordable.h"

#include "engine/component/render/renderable.h"
#include "engine/component/render/resource.h"

#include "engine/actor/tank/player_tank.h"
#include "engine/actor/tank/enemy_tank.h"
#include "engine/actor/power_up/base_power_up.h"
#include "engine/actor/headquarter.h"

namespace NSEngine {
	namespace NSActor {

		enum EGameMasterState : uint32_t {

		};

		struct CGameMasterRecord
			: public NSCore::CRecord {

			CGameMasterRecord(
				uint32_t id
			);

		};
		typedef CGameMasterRecord* pGameMasterRecord;

		class CGameMaster
			: public NSCore::CGameObject

			, public NSComponent::CUpdatable
			, public NSComponent::CRecordable

			, public NSComponent::CRenderable
			, public NSComponent::CResource
		{
		protected:
			// Children
			pHeadquarter headquarter = nullptr;
			std::map<uint32_t, pPlayerTank> player_tanks;
			std::map<uint32_t, std::pair<float, float>> player_spawn_positions;

			std::map<uint32_t, pBaseTank> enemy_tanks;
			std::map<uint32_t, std::pair<float, float>> enemy_spawn_positions;

			std::map<uint32_t, pBasePowerUp> power_ups;
			std::map<uint32_t, std::pair<float, float>> power_up_positions;
			
			std::map<uint32_t, std::tuple<uint32_t, uint32_t, uint32_t>> player_stats;

			bool started = false;

			sf::Sprite main_ui_frame_sprite;

		public:
			CGameMaster(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CGameMaster();

			void AddHeadquarter(std::string name);
			void AddPlayerTank(std::string name);
			void AddEnemyTank(std::string name);
			void AddPowerUp(std::string name);

			void ActivateFreeze();
			void ActivateGrenade();
			void ActivateShovel();

			void SpawnPlayerTank(uint32_t player_id);
			void DespawnPlayerTank(uint32_t player_id);

			void SpawnEnemyTank(uint32_t wave_id, uint32_t pos);
			void DespawnEnemyTank(uint32_t player_id);

			void SpawnPowerUp(uint32_t power_up_type, uint32_t pos);
			void DespawnPowerUp(uint32_t player_id);

			void LoadResource() override;
			void UnloadResource() override;

			void Serialize(uint32_t tick) override;
			void Deserialize(NSCore::pRecord record) override;

			void PackRecord(NSNetworks::CPacket* packet, NSCore::pRecord record) override;
			NSCore::pRecord UnpackRecord(NSNetworks::CPacket* packet) override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void LoadComponents(nlohmann::json& components_data) override;

		};
		typedef CGameMaster* pGameMaster;

	}
}

#endif // !__ENGINE__ACTOR__GAME_MASTER_H__
