#include "engine/actor/effect/explosion.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

#include "engine/actor/tank/base_tank.h"

namespace NSEngine {
	namespace NSActor {

		CExplosion::CExplosion(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world, id, name)
		{
			type = EActorType::EXPLOSION;
		}

		CExplosion::~CExplosion() {
		}

		void CExplosion::AddBaseTank(std::string name) {
			uint32_t id = world->dictionary[name];
			NSCore::pGameObject game_object = world->game_objects[id].get();
			base_tank = dynamic_cast<pBaseTank>(game_object);
			base_tank->AddExplosionEffect(GetName());
		}

		void CExplosion::SetPosition(float value_x, float value_y) {
			x = value_x;
			y = value_y;
		}

		void CExplosion::GetPosition(float& out_x, float& out_y) {
			out_x = x;
			out_y = y;
		}

		void CExplosion::LoadResource() {
			std::ifstream data_file(resource_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

		}

		void CExplosion::UnloadResource() {
		}

		void CExplosion::Update(float elapsed) {
		}

		void CExplosion::Render(sf::RenderWindow& window) {
		}

		void CExplosion::PackLoadPacket(NSNetworks::CPacket* packet) {
			NSCore::CGameObject::PackLoadPacket(packet);

			std::string base_tank_name = base_tank->GetName();
			*packet << base_tank_name;
		}

		void CExplosion::UnpackLoadPacket(NSNetworks::CPacket* packet) {
			NSCore::CGameObject::UnpackLoadPacket(packet);

			std::string base_tank_name;
			*packet >> base_tank_name;
			AddBaseTank(base_tank_name);
		}

	}
}