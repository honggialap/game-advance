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
				auto& game_master = data.at("game_master");
				NSServer::NSActor::CGameMaster::Create(game, this, game_master);
			}

			if (data.contains("player_tanks")) {
				auto& player_tanks = data.at("player_tanks");
				for (auto& player_tank : player_tanks) {
					NSServer::NSActor::CPlayerTank::Create(game, this, player_tank);

					if (player_tank.contains("bullets")) {
						auto& bullets = player_tank.at("bullets");
						for (auto& bullet : bullets) {
							NSServer::NSActor::CPlayerBullet::Create(game, this, bullet);
						}
					}
				}
			}

			if (data.contains("headquarters")) {
				auto& headquarters = data.at("headquarters");
				for (auto& headquarter : headquarters) {
					NSServer::NSActor::CHeadquarter::Create(game, this, headquarter);
				}
			}

			if (data.contains("factories")) {
				auto& factories = data.at("factories");
				for (auto& factory : factories) {
					NSServer::NSActor::CFactory::Create(game, this, factory);

					if (factories.contains("creep_tanks")) {
						auto& creep_tanks = factory.at("creep_tanks");
						for (auto& creep_tank : creep_tanks) {
							NSServer::NSActor::CCreepTank::Create(game, this, creep_tank);

							if (creep_tank.contains("bullets")) {
								auto& bullets = creep_tank.at("bullets");
								for (auto& bullet : bullets) {
									NSServer::NSActor::CCreepBullet::Create(game, this, bullet);
								}
							}
						}
					}
				}
			}

			if (data.contains("turrets")) {
				auto& turrets = data.at("turrets");
				for (auto& turret : turrets) {
					NSServer::NSActor::CTurret::Create(game, this, turret);

					if (turret.contains("bullets")) {
						auto& bullets = turret.at("bullets");
						for (auto& bullet : bullets) {
							NSServer::NSActor::CTurretBullet::Create(game, this, bullet);
						}
					}
				}
			}

			if (data.contains("bounds")) {
				auto& bounds = data.at("bounds");
				for (auto& bound : bounds) {
					NSServer::NSActor::CBound::Create(game, this, bound);
				}
			}

			if (data.contains("walls")) {
				auto& walls = data.at("walls");
				for (auto& wall : walls) {
					NSServer::NSActor::CWall::Create(game, this, wall);
				}
			}

			if (data.contains("waters")) {
				auto& waters = data.at("waters");
				for (auto& water : waters) {
					NSServer::NSActor::CWater::Create(game, this, water);
				}
			}

			if (data.contains("trees")) {
				auto& trees = data.at("trees");
				for (auto& tree : trees) {
					NSServer::NSActor::CTree::Create(game, this, tree);
				}
			}

			if (data.contains("repair_kits")) {
				auto& repair_kits = data.at("repair_kits");
				for (auto& repair_kit : repair_kits) {
					NSServer::NSActor::CRepairKit::Create(game, this, repair_kit);
				}
			}

			if (data.contains("power_ups")) {
				auto& power_ups = data.at("power_ups");
				for (auto& power_up : power_ups) {
					NSServer::NSActor::CPowerUp::Create(game, this, power_up);
				}
			}

		}

		void CWorld::Unload() {

		}
	}
}

