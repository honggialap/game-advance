#include "engine/actor/tank/base_tank.h"
#include "engine/core/world.h"

#include "engine/actor/game_master.h"
#include "engine/actor/tank/bullet.h"

namespace NSEngine {
	namespace NSActor {

		CBaseTank::CBaseTank(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		) 
			: NSCore::CGameObject(game, world, id, name)
			, NSComponent::CPhysics(world->physics_world)
		{
			type = INVALID_ACTOR;
		}

		CBaseTank::~CBaseTank() {
		}

		void CBaseTank::AddBullet(std::string name) {
			uint32_t id = world->dictionary[name];
			NSCore::pGameObject game_object = world->game_objects[id].get();

			pBullet bullet = dynamic_cast<pBullet>(game_object);
			bullets.push_back(bullet);
		}

		void CBaseTank::AddExplosionEffect(std::string name) {
			uint32_t id = world->dictionary[name];
			NSCore::pGameObject game_object = world->game_objects[id].get();
			explosion_effect = dynamic_cast<pExplosion>(game_object);
		}

		void CBaseTank::PackLoadPacket(NSNetworks::CPacket* packet) {
			NSCore::CGameObject::PackLoadPacket(packet);

			std::string game_master_name = game_master->GetName();
			*packet << game_master_name;
		}

		void CBaseTank::UnpackLoadPacket(NSNetworks::CPacket* packet) {
			NSCore::CGameObject::UnpackLoadPacket(packet);

			std::string game_master_name;
			*packet >> game_master_name;
			AddGameMaster(game_master_name);
		}

	}
}