#include "server/core/world.h"

#include "server/actor/game_master.h"
#include "server/actor/player_tank.h"
#include "server/actor/player_bullet.h"
#include "server/actor/creep_tank.h"
#include "server/actor/creep_bullet.h"
#include "server/actor/turret.h"
#include "server/actor/turret_bullet.h"
#include "server/actor/headquarter.h"
#include "server/actor/factory.h"
#include "server/actor/repair_kit.h"
#include "server/actor/power_up.h"
#include "server/actor/bound.h"
#include "server/actor/wall.h"
#include "server/actor/tree.h"
#include "server/actor/water.h"

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

			if (data.contains("game_master")) {
				auto& game_master_data = data.at("game_master");
				std::string game_master_name = game_master_data.at("name");
				NSActor::CGameMaster::Create(game, this, game_master_name, game_master_data);
			}

			if (data.contains("repair_kits")) {
				auto& repair_kit_data = data.at("repair_kits");
				uint32_t repair_kit_count = repair_kit_data.at("count");

				for (uint32_t sub_id = 1; sub_id <= repair_kit_count; sub_id++) {
					std::stringstream name;
					std::string repair_kit_name = repair_kit_data.at("name");
					name << repair_kit_name << "_" << sub_id;
					auto repair_kit = NSActor::CRepairKit::Create(game, this, name.str(), repair_kit_data);

					std::string parent_name = repair_kit_data.at("parent");
					repair_kit->AddParent(parent_name);

					//repair_kit->SetActive(false);
					//repair_kit->SetVisible(false);
				}
			}

			if (data.contains("power_ups")) {
				auto& power_up_data = data.at("power_ups");
				uint32_t power_up_count = power_up_data.at("count");

				for (uint32_t sub_id = 1; sub_id <= power_up_count; sub_id++) {
					std::stringstream name;
					std::string power_up_name = power_up_data.at("name");
					name << power_up_name << "_" << sub_id;
					auto power_up = NSActor::CPowerUp::Create(game, this, name.str(), power_up_data);

					std::string parent_name = power_up_data.at("parent");
					power_up->AddParent(parent_name);

					//power_up->SetActive(false);
					//power_up->SetVisible(false);
				}
			}

			if (data.contains("player_tanks")) {
				for (auto& player_tank_data : data.at("player_tanks").at("individual")) {
					auto shared = data.at("player_tanks").at("shared");
					player_tank_data.insert(shared.begin(), shared.end());

					std::string player_tank_name = player_tank_data.at("name");
					auto player_tank = NSActor::CPlayerTank::Create(game, this, player_tank_name, player_tank_data);

					float x = player_tank_data.at("x");
					float y = player_tank_data.at("y");
					player_tank->SetPosition(x, y);

					std::string parent_name = player_tank_data.at("parent");
					player_tank->AddParent(parent_name);

					auto bullet_data = data.at("player_tanks").at("bullets");
					uint32_t bullet_count = bullet_data.at("count");
					std::string player_bullet_default_name = bullet_data.at("name");

					for (uint32_t i = 1; i <= bullet_count; i++) {
						std::stringstream player_bullet_name_stream;
						player_bullet_name_stream << player_tank_name <<
							"_" << player_bullet_default_name <<
							"_" << i;

						std::string player_bullet_name = player_bullet_name_stream.str();
						auto player_bullet = NSActor::CPlayerBullet::Create(game, this, player_bullet_name, bullet_data);
						player_bullet->AddParent(player_tank_name);
					}
				}
			}

			if (data.contains("headquarter")) {
				for (auto& headquarter_data : data.at("headquarters").at("individual")) {
					auto shared = data.at("headquarters").at("shared");
					headquarter_data.insert(shared.begin(), shared.end());

					std::string headquarter_name = headquarter_data.at("name");
					auto headquarter = NSActor::CHeadquarter::Create(game, this, headquarter_name, headquarter_data);

					float x = headquarter_data.at("x");
					float y = headquarter_data.at("y");
					headquarter->SetPosition(x, y);

					std::string parent_name = headquarter_data.at("parent");
					headquarter->AddParent(parent_name);
				}
			}

			if (data.contains("factory")) {
				for (auto& factory_data : data.at("factories").at("individual")) {
					auto shared = data.at("factories").at("shared");
					factory_data.insert(shared.begin(), shared.end());

					std::string factory_name = factory_data.at("name");
					auto factory = NSActor::CFactory::Create(game, this, factory_name, factory_data);

					float x = factory_data.at("x");
					float y = factory_data.at("y");
					factory->SetPosition(x, y);

					std::string parent_name = factory_data.at("parent");
					factory->AddParent(parent_name);
				}
			}

			if (data.contains("turrets")) {
				for (auto& turret_data : data.at("turrets").at("individual")) {
					auto shared = data.at("turrets").at("shared");
					turret_data.insert(shared.begin(), shared.end());

					std::string turret_name = turret_data.at("name");
					auto turret = NSActor::CTurret::Create(game, this, turret_name, turret_data);

					float x = turret_data.at("x");
					float y = turret_data.at("y");
					turret->SetPosition(x, y);

					std::string parent_name = turret_data.at("parent");
					turret->AddParent(parent_name);

					auto bullet_data = data.at("turrets").at("bullets");
					uint32_t bullet_count = bullet_data.at("count");
					std::string turret_bullet_default_name = bullet_data.at("name");

					for (uint32_t i = 1; i <= bullet_count; i++) {
						std::stringstream turret_bullet_name_stream;
						turret_bullet_name_stream << turret_name <<
							"_" << turret_bullet_default_name <<
							"_" << i;

						std::string turret_bullet_name = turret_bullet_name_stream.str();
						auto turret_bullet = NSActor::CTurretBullet::Create(game, this, turret_bullet_name, bullet_data);
						turret_bullet->AddParent(turret_name);
					}
				}
			}

			if (data.contains("creep_tanks")) {
				for (auto& creep_tank_data : data.at("creep_tanks").at("individual")) {
					auto shared = data.at("creep_tanks").at("shared");
					creep_tank_data.insert(shared.begin(), shared.end());

					std::string creep_tank_name = creep_tank_data.at("name");
					auto creep_tank = NSActor::CCreepTank::Create(game, this, creep_tank_name, creep_tank_data);

					float x = creep_tank_data.at("x");
					float y = creep_tank_data.at("y");
					creep_tank->SetPosition(x, y);

					std::string parent_name = creep_tank_data.at("parent");
					creep_tank->AddParent(parent_name);

					auto bullet_data = data.at("creep_tanks").at("bullets");
					uint32_t bullet_count = bullet_data.at("count");
					std::string creep_bullet_default_name = bullet_data.at("name");

					for (uint32_t i = 1; i <= bullet_count; i++) {
						std::stringstream creep_bullet_name_stream;
						creep_bullet_name_stream << creep_tank_name <<
							"_" << creep_bullet_default_name <<
							"_" << i;

						std::string creep_bullet_name = creep_bullet_name_stream.str();
						auto creep_bullet = NSActor::CCreepBullet::Create(game, this, creep_bullet_name, bullet_data);
						creep_bullet->AddParent(creep_tank_name);
					}
				}
			}

			//
			//if (data.contains("terrain")) {
			//	auto& terrain_data = data.at("terrain");
			//
			//	uint32_t horizontal_bound_count = 0;
			//	auto& horizontal_bound_data = terrain_data.at("horizontal_bound");
			//
			//	uint32_t vertical_bound_count = 0;
			//	auto& vertical_bound_data = terrain_data.at("vertical_bound");
			//
			//	uint32_t wall_count = 0;
			//	auto& wall_data = terrain_data.at("wall");
			//
			//	uint32_t water_count = 0;
			//	auto& water_data = terrain_data.at("water");
			//
			//	uint32_t tree_count = 0;
			//	auto& tree_data = terrain_data.at("tree");
			//
			//	auto& map_data = terrain_data.at("map");
			//	uint32_t columns = uint32_t(map_data.at("columns"));
			//	uint32_t rows = uint32_t(map_data.at("rows"));
			//	float tile_width = float(map_data.at("tile_width"));
			//	float tile_height = float(map_data.at("tile_height"));
			//
			//	std::vector<int32_t> tiles;
			//	for (auto& tile : map_data.at("data")) {
			//		tiles.push_back(tile);
			//	}
			//
			//	for (int32_t i = 0; i < tiles.size(); i++) {
			//		int32_t x = i % columns;
			//		int32_t y = rows - (i / columns) - 1;
			//
			//		float position_x = x * tile_width;
			//		float position_y = y * tile_height;
			//
			//		int32_t type = tiles[i];
			//		switch (type) {
			//			// horizontal bound
			//		case 10: {
			//			std::stringstream name;
			//			std::string bound_name = horizontal_bound_data.at("name");
			//			uint32_t sub_id = horizontal_bound_count++;
			//			name << bound_name << "_" << sub_id;
			//			auto bound = NSActor::CBound::Create(game, this, name.str(), horizontal_bound_data);
			//			bound->SetPosition(position_x, position_y);
			//			break;
			//		}
			//
			//			   // vertical bound
			//		case 11: {
			//			std::stringstream name;
			//			std::string bound_name = vertical_bound_data.at("name");
			//			uint32_t sub_id = vertical_bound_count++;
			//			name << bound_name << "_" << sub_id;
			//			auto bound = NSActor::CBound::Create(game, this, name.str(), vertical_bound_data);
			//			bound->SetPosition(position_x, position_y);
			//			break;
			//		}
			//
			//			   // wall
			//		case 20: {
			//			std::stringstream name;
			//			std::string wall_name = wall_data.at("name");
			//			uint32_t sub_id = wall_count++;
			//			name << wall_name << "_" << sub_id;
			//			auto wall = NSActor::CWall::Create(game, this, name.str(), wall_data);
			//			wall->SetPosition(position_x, position_y);
			//			break;
			//		}
			//
			//			   // water
			//		case 30: {
			//			std::stringstream name;
			//			std::string water_name = water_data.at("name");
			//			uint32_t sub_id = water_count++;
			//			name << water_name << "_" << sub_id;
			//			auto water = NSActor::CWater::Create(game, this, name.str(), water_data);
			//			water->SetPosition(position_x, position_y);
			//			break;
			//		}
			//
			//			   // tree
			//		case 40: {
			//			std::stringstream name;
			//			std::string tree_name = tree_data.at("name");
			//			uint32_t sub_id = tree_count++;
			//			name << tree_name << "_" << sub_id;
			//			auto tree = NSActor::CTree::Create(game, this, name.str(), water_data);
			//			tree->SetPosition(position_x, position_y);
			//			break;
			//		}
			//
			//		default: {
			//			break;
			//		}
			//
			//		}
			//	}
			//
			//
			//
			//}


		}

		void CWorld::Unload() {

		}
	}
}

