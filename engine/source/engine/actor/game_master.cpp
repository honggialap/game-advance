#include "engine/actor/game_master.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CGameMasterRecord::CGameMasterRecord(
			uint32_t id
		)
			: NSCore::CRecord(id) {
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

		void CGameMaster::AddHeadquarter(std::string name) {
			uint32_t id = world->dictionary[name];
			NSCore::pGameObject game_object = world->game_objects[id].get();
			headquarter = dynamic_cast<pHeadquarter>(game_object);
		}

		void CGameMaster::AddPlayerTank(std::string name) {
			uint32_t id = world->dictionary[name];
			NSCore::pGameObject game_object = world->game_objects[id].get();
			
			pPlayerTank player_tank = dynamic_cast<pPlayerTank>(game_object);
			uint32_t player_id = player_tank->GetPlayerId();

			player_tanks[player_id] = player_tank;
		}

		void CGameMaster::AddEnemyTank(std::string name) {
			uint32_t id = world->dictionary[name];
			NSCore::pGameObject game_object = world->game_objects[id].get();

			pEnemyTank enemy_tank = dynamic_cast<pEnemyTank>(game_object);
			uint32_t wave_id = enemy_tank->GetWave();

			enemy_tanks[wave_id] = enemy_tank;
		}

		void CGameMaster::AddPowerUp(std::string name) {
			uint32_t id = world->dictionary[name];
			NSCore::pGameObject game_object = world->game_objects[id].get();

			pBasePowerUp power_up = dynamic_cast<pBasePowerUp>(game_object);
			uint32_t power_up_type = power_up->GetType();

			power_ups[power_up_type] = power_up;
		}

		void CGameMaster::ActivateFreeze() {
			enemy_tanks;
		}

		void CGameMaster::ActivateGrenade() {
			enemy_tanks;
		}

		void CGameMaster::ActivateShovel() {
			headquarter->ActivateShovel();
		}

		void CGameMaster::SpawnPlayerTank(uint32_t player_id) {
			if (true) {
				auto player = player_tanks[player_id];
				float x = player_spawn_positions[player_id].first;
				float y = player_spawn_positions[player_id].second;

				//player->Reset();
				player->SetPosition(x, y);
				player->SetActive(true);
				player->SetVisible(true);
				player->SetBodyEnable(true);
			}
		}

		void CGameMaster::DespawnPlayerTank(uint32_t player_id) {
			if (true) {
				auto player = player_tanks[player_id];
				player->SetActive(false);
				player->SetVisible(false);
				player->SetBodyEnable(false);
			}
		}

		void CGameMaster::SpawnEnemyTank(uint32_t wave_id, uint32_t pos) {
			if (true) {
				auto enemy = enemy_tanks[wave_id];
				float x = enemy_spawn_positions[pos].first;
				float y = enemy_spawn_positions[pos].second;

				//enemy->Reset();
				enemy->SetPosition(x, y);
				enemy->SetActive(true);
				enemy->SetVisible(true);
				enemy->SetBodyEnable(true);
			}
		}

		void CGameMaster::DespawnEnemyTank(uint32_t wave_id) {
			if (true) {
				auto enemy = enemy_tanks[wave_id];
				enemy->SetActive(false);
				enemy->SetVisible(false);
				enemy->SetBodyEnable(false);
			}
		}

		void CGameMaster::SpawnPowerUp(uint32_t power_up_type, uint32_t pos) {
			if (true) {
				auto power_up = power_ups[power_up_type];
				float x = power_up_positions[pos].first;
				float y = power_up_positions[pos].second;

				//power_up->Reset();
				power_up->SetPosition(x, y);
				power_up->SetActive(true);
				power_up->SetVisible(true);
				power_up->SetBodyEnable(true);
			}
		}

		void CGameMaster::DespawnPowerUp(uint32_t power_up_type) {
			if (true) {
				auto power_up = power_ups[power_up_type];
				power_up->SetActive(false);
				power_up->SetVisible(false);
				power_up->SetBodyEnable(false);
			}
		}

		void CGameMaster::LoadResource() {
			std::ifstream data_file(resource_path);
			nlohmann::json data = nlohmann::json::parse(data_file);
			
			uint32_t texture_id = data.at("main_ui_frame_texture");
			sf::Texture& texture = game->GetTexture(texture_id);

			main_ui_frame_sprite.setTexture(texture);
			main_ui_frame_sprite.setPosition(sf::Vector2f(0.0f, 0.0f));
		}

		void CGameMaster::UnloadResource() {
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
			//*packet << a;
		}

		NSCore::pRecord CGameMaster::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CGameMasterRecord(id);
			//*packet >> record->match_time;

			return record;
		}

		void CGameMaster::Update(float elapsed) {
		}

		void CGameMaster::Render(sf::RenderWindow& window) {
			window.draw(main_ui_frame_sprite);
		}

		void CGameMaster::LoadComponents(nlohmann::json& components_data) {
			NSCore::CGameObject::LoadComponents(components_data);

			for (auto& spawn_position : components_data.at("player_spawn_positions")) {
				uint32_t player_id = spawn_position.at("player_id");
				float x = spawn_position.at("x");
				float y = spawn_position.at("y");
				player_spawn_positions[player_id] = std::make_pair(x, y);
			}

			uint32_t enemy_spawn_position_counter = 0;
			for (auto& spawn_position : components_data.at("enemy_spawn_positions")) {
				float x = spawn_position.at("x");
				float y = spawn_position.at("y");
				enemy_spawn_positions[enemy_spawn_position_counter] = std::make_pair(x, y);
				enemy_spawn_position_counter += 1;
			}

			uint32_t power_up_spawn_position_counter = 0;
			for (auto& spawn_position : components_data.at("power_up_spawn_positions")) {
				float x = spawn_position.at("x");
				float y = spawn_position.at("y");
				power_up_positions[power_up_spawn_position_counter] = std::make_pair(x, y);
				power_up_spawn_position_counter += 1;
			}
		}

	}
}