#include "engine/actor/power_up/base_power_up.h"
#include "engine/core/world.h"

#include "engine/actor/game_master.h"

namespace NSEngine {
	namespace NSActor {

		CBasePowerUp::CBasePowerUp(
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

		CBasePowerUp::~CBasePowerUp() {
		}

		void CBasePowerUp::AddGameMaster(std::string name) {
			uint32_t id = world->dictionary[name];
			NSCore::pGameObject game_object = world->game_objects[id].get();
			game_master = dynamic_cast<pGameMaster>(game_object);
			game_master->AddPowerUp(GetName());
		}

		void CBasePowerUp::LoadResource() {
			std::ifstream data_file(resource_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

			std::string texture_source = data.at("texture");
			texture.loadFromFile(texture_source);

			auto& sprite_data = data.at("sprite");
			float origin_x = sprite_data.at("origin_x");
			float origin_y = sprite_data.at("origin_y");
			sprite = sf::Sprite(texture);
			sprite.setOrigin(origin_x, origin_y);
		}

		void CBasePowerUp::UnloadResource()
		{
		}

		void CBasePowerUp::PackLoadPacket(NSNetworks::CPacket* packet) {
			NSCore::CGameObject::PackLoadPacket(packet);

			std::string game_master_name = game_master->GetName();
			*packet << game_master_name;
		}

		void CBasePowerUp::UnpackLoadPacket(NSNetworks::CPacket* packet) {
			NSCore::CGameObject::UnpackLoadPacket(packet);

			std::string game_master_name;
			*packet >> game_master_name;
			AddGameMaster(game_master_name);
		}

	}
}