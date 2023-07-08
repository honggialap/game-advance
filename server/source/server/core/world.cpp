#include "server/core/world.h"

#include "server/actor/game_master.h"
#include "server/actor/headquarter.h"

#include "server/actor/tank/player_tank.h"
#include "server/actor/tank/basic_tank.h"
#include "server/actor/tank/fast_tank.h"
#include "server/actor/tank/power_tank.h"
#include "server/actor/tank/armor_tank.h"
#include "server/actor/tank/bullet.h"

#include "server/actor/power_up/grenade.h"
#include "server/actor/power_up/helmet.h"
#include "server/actor/power_up/shovel.h"
#include "server/actor/power_up/star.h"
#include "server/actor/power_up/tank.h"
#include "server/actor/power_up/timer.h"

#include "server/actor/terrain/bound.h"
#include "server/actor/terrain/brick.h"
#include "server/actor/terrain/ice.h"
#include "server/actor/terrain/steel.h"
#include "server/actor/terrain/tree.h"
#include "server/actor/terrain/water.h"

#include "server/actor/effect/explosion.h"
#include "server/actor/effect/impact.h"
#include "server/actor/effect/score.h"

namespace NSServer {
	namespace NSCore {

		CWorld::CWorld(NSEngine::NSCore::pGame game)
			: NSEngine::NSCore::CWorld(game)
			, game_server(static_cast<NSServer::NSCore::pGame>(game)) {
		}

		CWorld::~CWorld() {
		}

		bool CWorld::IsRollback() {
			return rollback;
		}

		void CWorld::SetRollback(bool value) {
			rollback = value;
		}

		uint32_t CWorld::GetRollbackTick() {
			return rollback_tick;
		}

		void CWorld::SetRollbackTick(uint32_t value) {
			rollback_tick = value;
		}

		void CWorld::Load(nlohmann::json& data) {

			// Game Master
			auto& game_master_data = data.at("actors").at("game_master");
			std::string game_master_name = game_master_data.at("name");
			auto game_master = NSActor::CGameMaster::Create(game, this, game_master_name, game_master_data);

			// Pickups
			/*
			{
				auto& grenade_data = data.at("actors").at("grenade");
				std::string grenade_name = grenade_data.at("name");
				auto grenade = NSActor::CGrenade::Create(game, this, grenade_name, grenade_data);
				grenade->AddGameMaster(game_master_name);

				auto& helmet_data = data.at("actors").at("helmet");
				std::string helmet_name = helmet_data.at("name");
				auto helmet = NSActor::CHelmet::Create(game, this, helmet_name, helmet_data);
				helmet->AddGameMaster(game_master_name);

				auto& shovel_data = data.at("actors").at("shovel");
				std::string shovel_name = shovel_data.at("name");
				auto shovel = NSActor::CShovel::Create(game, this, shovel_name, shovel_data);
				shovel->AddGameMaster(game_master_name);

				auto& star_data = data.at("actors").at("star");
				std::string star_name = star_data.at("name");
				auto star = NSActor::CStar::Create(game, this, star_name, star_data);
				star->AddGameMaster(game_master_name);

				auto& tank_data = data.at("actors").at("tank");
				std::string tank_name = tank_data.at("name");
				auto tank = NSActor::CTank::Create(game, this, tank_name, tank_data);
				tank->AddGameMaster(game_master_name);

				auto& timer_data = data.at("actors").at("timer");
				std::string timer_name = timer_data.at("name");
				auto timer = NSActor::CTimer::Create(game, this, timer_name, timer_data);
				timer->AddGameMaster(game_master_name);
			}
			*/

			// Headquarter
			{
				auto& headquarter_data = data.at("actors").at("headquarter");
				std::string headquarter_name = headquarter_data.at("name");
				auto headquarter = NSActor::CHeadquarter::Create(game, this, headquarter_name, headquarter_data);
				headquarter->AddGameMaster(game_master_name);

				float x = headquarter_data.at("x");
				float y = headquarter_data.at("y");
				headquarter->SetPosition(x, y);

				auto& brick_data = data.at("actors").at("brick");
				//auto& steel_data = data.at("actors").at("steel");

				uint32_t counter_id = 0;
				for (auto& iterator : headquarter_data.at("bounds")) {
					float x = iterator.at("x");
					float y = iterator.at("y");

					std::string brick_default_name = brick_data.at("name");
					std::stringstream brick_name_stream;
					brick_name_stream
						<< headquarter_name
						<< "_" << brick_default_name
						<< "_" << counter_id;
					std::string brick_name = brick_name_stream.str();

					auto brick = NSActor::CBrick::Create(game, this, brick_name, brick_data);
					brick->SetPosition(x, y);
					brick->AddHeadquarter(headquarter_name);

					//std::string steel_default_name = steel_data.at("name");
					//std::stringstream steel_name_stream;
					//steel_name_stream
					//	<< headquarter_name
					//	<< "_" << steel_default_name
					//	<< "_" << counter_id;
					//std::string steel_name = steel_name_stream.str();
					//
					//auto steel = NSActor::CSteel::Create(game, this, steel_name, steel_data);
					//steel->SetPosition(x, y);
					//steel->AddHeadquarter(headquarter_name);
					//steel->SetVisible(false);
					//steel->SetActive(false);
					//steel->SetBodyEnable(false);
					
					counter_id += 1;
				}
			}

			// Players tank
			{
				for (auto& player_tank_data : data.at("actors").at("player_tanks")) {
					std::string player_tank_name = player_tank_data.at("name");
					auto player_tank = NSActor::CPlayerTank::Create(game, this, player_tank_name, player_tank_data);
					player_tank->AddGameMaster(game_master_name);

					// Effect
					/*
					{
						auto& explosion_data = data.at("actors").at("explosion");
						std::string explosion_default_name = explosion_data.at("name");
						std::stringstream explosion_name_stream;
						explosion_name_stream
							<< player_tank_name
							<< "_" << explosion_default_name;
						std::string explosion_name = explosion_name_stream.str();

						auto explosion = NSActor::CExplosion::Create(game, this, explosion_name, explosion_data);
						explosion->AddBaseTank(player_tank_name);
					}
					*/

					// Bullet
					{
						auto& bullet_data = data.at("actors").at("player_bullet");
						std::string bullet_default_name = bullet_data.at("name");

						//auto& impact_data = data.at("actors").at("impact");
						//std::string impact_default_name = impact_data.at("name");

						for (uint32_t bullet_id = 0; bullet_id < 1; bullet_id++) {

							std::stringstream bullet_name_stream;
							bullet_name_stream
								<< player_tank_name
								<< "_" << bullet_default_name
								<< "_" << bullet_id;
							std::string bullet_name = bullet_name_stream.str();

							auto bullet = NSActor::CBullet::Create(game, this, bullet_name, bullet_data);
							bullet->AddBaseTank(player_tank_name);

							//std::stringstream impact_name_stream;
							//impact_name_stream
							//	<< bullet_name
							//	<< "_" << impact_default_name;
							//std::string impact_name = impact_name_stream.str();
							//
							//auto impact = NSActor::CImpact::Create(game, this, impact_name, impact_data);
							//impact->AddBullet(bullet_name);
						}
					}
				}
			}

			// Enemy tanks
			{
				auto& basic_tank_data = data.at("actors").at("basic_tank");
				auto& basic_tank_red_data = data.at("actors").at("basic_tank_red");

				auto& fast_tank_data = data.at("actors").at("fast_tank");
				auto& fast_tank_red_data = data.at("actors").at("fast_tank_red");

				auto& power_tank_data = data.at("actors").at("power_tank");
				auto& power_tank_red_data = data.at("actors").at("power_tank_red");

				auto& armor_tank_data = data.at("actors").at("armor_tank");
				auto& armor_tank_red_data = data.at("actors").at("armor_tank_red");

				auto& enemy_bullet_data = data.at("actors").at("enemy_bullet");

				std::vector<int32_t> waves;
				for (auto& wave : data.at("wave")) {
					waves.push_back(wave);
				}

				for (int32_t wave_counter = 0; wave_counter < waves.size(); wave_counter++) {
					NSEngine::NSActor::pEnemyTank enemy_tank = nullptr;

					int32_t enemy_type = waves[wave_counter];
					switch (enemy_type) {

					case 1: { // BASIC
						std::string enemy_tank_default_name = basic_tank_data.at("name");
						std::stringstream name_stream;
						name_stream
							<< enemy_tank_default_name
							<< "_" << wave_counter;
						std::string enemy_tank_name = name_stream.str();

						enemy_tank = NSActor::CBasicTank::Create(game, this, enemy_tank_name, basic_tank_data);
						enemy_tank->SetWave(wave_counter);
						enemy_tank->AddGameMaster(game_master_name);
						break;
					}

					case 2: { // BASIC_RED
						std::string enemy_tank_default_name = basic_tank_red_data.at("name");
						std::stringstream name_stream;
						name_stream
							<< enemy_tank_default_name
							<< "_" << wave_counter;
						std::string enemy_tank_name = name_stream.str();
						enemy_tank = NSActor::CBasicTank::Create(game, this, enemy_tank_name, basic_tank_red_data);
						enemy_tank->SetWave(wave_counter);
						enemy_tank->AddGameMaster(game_master_name);
						break;
					}

					case 3: { // FAST
						std::string enemy_tank_default_name = fast_tank_data.at("name");
						std::stringstream name_stream;
						name_stream
							<< enemy_tank_default_name
							<< "_" << wave_counter;
						std::string enemy_tank_name = name_stream.str();
						enemy_tank = NSActor::CFastTank::Create(game, this, enemy_tank_name, fast_tank_data);
						enemy_tank->SetWave(wave_counter);
						enemy_tank->AddGameMaster(game_master_name);
						break;
					}

					case 4: { // FAST_RED
						std::string enemy_tank_default_name = fast_tank_red_data.at("name");
						std::stringstream name_stream;
						name_stream
							<< enemy_tank_default_name
							<< "_" << wave_counter;
						std::string enemy_tank_name = name_stream.str();
						enemy_tank = NSActor::CFastTank::Create(game, this, enemy_tank_name, fast_tank_red_data);
						enemy_tank->SetWave(wave_counter);
						enemy_tank->AddGameMaster(game_master_name);
						break;
					}

					case 5: { // POWER
						std::string enemy_tank_default_name = power_tank_data.at("name");
						std::stringstream name_stream;
						name_stream
							<< enemy_tank_default_name
							<< "_" << wave_counter;
						std::string enemy_tank_name = name_stream.str();
						enemy_tank = NSActor::CPowerTank::Create(game, this, enemy_tank_name, power_tank_data);
						enemy_tank->SetWave(wave_counter);
						enemy_tank->AddGameMaster(game_master_name);
						break;
					}

					case 6: { // POWER_RED
						std::string enemy_tank_default_name = power_tank_red_data.at("name");
						std::stringstream name_stream;
						name_stream
							<< enemy_tank_default_name
							<< "_" << wave_counter;
						std::string enemy_tank_name = name_stream.str();
						enemy_tank = NSActor::CBasicTank::Create(game, this, enemy_tank_name, power_tank_red_data);
						enemy_tank->SetWave(wave_counter);
						enemy_tank->AddGameMaster(game_master_name);
						break;
					}

					case 7: { // ARMOR
						std::string enemy_tank_default_name = armor_tank_data.at("name");
						std::stringstream name_stream;
						name_stream
							<< enemy_tank_default_name
							<< "_" << wave_counter;
						std::string enemy_tank_name = name_stream.str();
						enemy_tank = NSActor::CBasicTank::Create(game, this, enemy_tank_name, armor_tank_data);
						enemy_tank->SetWave(wave_counter);
						enemy_tank->AddGameMaster(game_master_name);
						break;
					}

					case 8: { // ARMOR_RED
						std::string enemy_tank_default_name = armor_tank_red_data.at("name");
						std::stringstream name_stream;
						name_stream
							<< enemy_tank_default_name
							<< "_" << wave_counter;
						std::string enemy_tank_name = name_stream.str();
						enemy_tank = NSActor::CBasicTank::Create(game, this, enemy_tank_name, armor_tank_red_data);
						enemy_tank->SetWave(wave_counter);
						enemy_tank->AddGameMaster(game_master_name);
						break;
					}

					}

					if (enemy_tank != nullptr) {
						std::string enemy_tank_name = enemy_tank->GetName();

						// Effect
						/*
						{
							auto& explosion_data = data.at("actors").at("explosion");
							std::string explosion_default_name = explosion_data.at("name");
							std::stringstream explosion_name_stream;
							explosion_name_stream
								<< enemy_tank_name
								<< "_" << explosion_default_name;
							std::string explosion_name = explosion_name_stream.str();

							auto explosion = NSActor::CExplosion::Create(game, this, explosion_name, explosion_data);
							explosion->AddBaseTank(enemy_tank_name);
						}

						// Score
						{
							auto& score_data = data.at("actors").at("score");
							std::string score_default_name = score_data.at("name");
							std::stringstream score_name_stream;
							score_name_stream
								<< enemy_tank_name
								<< "_" << score_default_name;
							std::string score_name = score_name_stream.str();

							auto score = NSActor::CScore::Create(game, this, score_name, score_data);
							score->AddEnemyTank(enemy_tank_name);
						}
						*/

						// Bullet
						{
							auto& bullet_data = data.at("actors").at("enemy_bullet");
							std::string bullet_default_name = bullet_data.at("name");

							//auto& impact_data = data.at("actors").at("impact");
							//std::string impact_default_name = impact_data.at("name");

							for (uint32_t bullet_id = 0; bullet_id < 1; bullet_id++) {

								std::stringstream bullet_name_stream;
								bullet_name_stream
									<< enemy_tank_name
									<< "_" << bullet_default_name
									<< "_" << bullet_id;
								std::string bullet_name = bullet_name_stream.str();

								auto bullet = NSActor::CBullet::Create(game, this, bullet_name, bullet_data);
								bullet->AddBaseTank(enemy_tank_name);

								//std::stringstream impact_name_stream;
								//impact_name_stream
								//	<< bullet_name
								//	<< "_" << impact_default_name;
								//std::string impact_name = impact_name_stream.str();
								//
								//auto impact = NSActor::CImpact::Create(game, this, impact_name, impact_data);
								//impact->AddBullet(bullet_name);
							}
						}

					}
				}
			}

			// Terrain
			{
				for (auto& bound_data : data.at("map_bounds")) {
					std::string name = bound_data.at("name");
					float x = bound_data.at("x");
					float y = bound_data.at("y");

					auto bound = NSActor::CBound::Create(game, this, name, bound_data);
					bound->SetPosition(x, y);
				}

				/*

				auto& brick_data = data.at("actors").at("brick");
				auto& steel_data = data.at("actors").at("steel");
				auto& ice_data = data.at("actors").at("ice");
				auto& tree_data = data.at("actors").at("tree");
				auto& water_data = data.at("actors").at("water");

				auto& map_data = data.at("map_terrain");
				uint32_t columns = uint32_t(map_data.at("columns"));
				uint32_t rows = uint32_t(map_data.at("rows"));
				float tile_width = float(map_data.at("tile_width"));
				float tile_height = float(map_data.at("tile_height"));
				float offset_x = float(map_data.at("offset_x"));
				float offset_y = float(map_data.at("offset_y"));

				std::vector<int32_t> tiles;
				for (auto& tile : map_data.at("data")) {
					tiles.push_back(tile);
				}

				for (int32_t tile = 0; tile < tiles.size(); tile++) {
					int32_t x = tile % columns;
					int32_t y = rows - (tile / columns) - 1;

					float position_x = (x * tile_width) + offset_x;
					float position_y = (y * tile_height) + offset_y;

					int32_t type = tiles[tile];
					switch (type) {

					case 0: { // BLANK
						break;
					}

					case 1: { // BRICK
						std::stringstream terrain_name_stream;
						std::string default_name = brick_data.at("name");
						terrain_name_stream
							<< default_name
							<< "_" << tile;
						std::string terrain_name = terrain_name_stream.str();

						auto terrain = NSActor::CBrick::Create(game, this, terrain_name, brick_data);
						terrain->SetPosition(position_x, position_y);
						break;
					}

					case 2: { // STEEL
						std::stringstream terrain_name_stream;
						std::string default_name = steel_data.at("name");
						terrain_name_stream
							<< default_name
							<< "_" << tile;
						std::string terrain_name = terrain_name_stream.str();

						auto terrain = NSActor::CSteel::Create(game, this, terrain_name, steel_data);
						terrain->SetPosition(position_x, position_y);
						break;
					}

					case 3: { // TREE
						std::stringstream terrain_name_stream;
						std::string default_name = tree_data.at("name");
						terrain_name_stream
							<< default_name
							<< "_" << tile;
						std::string terrain_name = terrain_name_stream.str();

						auto terrain = NSActor::CTree::Create(game, this, terrain_name, tree_data);
						terrain->SetPosition(position_x, position_y);
						break;
					}

					case 4: { // WATER
						std::stringstream terrain_name_stream;
						std::string default_name = water_data.at("name");
						terrain_name_stream
							<< default_name
							<< "_" << tile;
						std::string terrain_name = terrain_name_stream.str();

						auto terrain = NSActor::CWater::Create(game, this, terrain_name, water_data);
						terrain->SetPosition(position_x, position_y);
						break;
					}

					case 5: { // ICE
						std::stringstream terrain_name_stream;
						std::string default_name = ice_data.at("name");
						terrain_name_stream
							<< default_name
							<< "_" << tile;
						std::string terrain_name = terrain_name_stream.str();

						auto terrain = NSActor::CIce::Create(game, this, terrain_name, ice_data);
						terrain->SetPosition(position_x, position_y);
						break;
					}

					default: {
						break;
					}

					}
				}
				*/
			}

		}

		void CWorld::Unload() {

		}
	}
}

