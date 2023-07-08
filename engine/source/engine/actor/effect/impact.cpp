#include "engine/actor/effect/impact.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

#include "engine/actor/tank/bullet.h"

namespace NSEngine {
	namespace NSActor {

		CImpact::CImpact(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world, id, name)
		{
			type = EActorType::IMPACT;
		}

		CImpact::~CImpact() {
		}

		void CImpact::AddBullet(std::string name) {
			uint32_t id = world->dictionary[name];
			NSCore::pGameObject game_object = world->game_objects[id].get();
			bullet = dynamic_cast<pBullet>(game_object);
			bullet->AddImpactEffect(GetName());
		}

		void CImpact::SetPosition(float value_x, float value_y) {
			x = value_x;
			y = value_y;
		}

		void CImpact::GetPosition(float& out_x, float& out_y) {
			out_x = x;
			out_y = y;
		}

		void CImpact::LoadResource() {
			std::ifstream data_file(resource_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

		}

		void CImpact::UnloadResource() {
		}

		void CImpact::Update(float elapsed) {
		}

		void CImpact::Render(sf::RenderWindow& window) {
		}

		void CImpact::PackLoadPacket(NSNetworks::CPacket* packet) {
			NSCore::CGameObject::PackLoadPacket(packet);

			std::string bullet_name = bullet->GetName();
			*packet << bullet_name;
		}

		void CImpact::UnpackLoadPacket(NSNetworks::CPacket* packet) {
			NSCore::CGameObject::UnpackLoadPacket(packet);

			std::string bullet_name;
			*packet >> bullet_name;
			AddBullet(bullet_name);
		}

	}
}