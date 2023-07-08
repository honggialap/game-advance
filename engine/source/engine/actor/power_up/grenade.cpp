#include "engine/actor/power_up/grenade.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CGrenadeRecord::CGrenadeRecord(uint32_t id)
			: NSCore::CRecord(id) {
			actor_type = EActorType::GRENADE;
		}

		CGrenade::CGrenade(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSActor::CBasePowerUp(game, world, id, name)
		{
			type = EActorType::GRENADE;
		}

		CGrenade::~CGrenade() {
		}

		void CGrenade::Serialize(uint32_t tick) {
			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CGrenadeRecord>(
					id
				)
			);
		}

		void CGrenade::Deserialize(NSCore::pRecord record) {
			auto grenade_record = static_cast<pGrenadeRecord>(record);
		}

		void CGrenade::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto grenade_record = static_cast<pGrenadeRecord>(record);
			//*packet << factory_record->a;
		}

		NSCore::pRecord CGrenade::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CGrenadeRecord(id);

			//*packet >> factory_record->a;

			return record;
		}

		void CGrenade::Update(float elapsed) {
		}

		void CGrenade::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CGrenade::OnCollisionEnter(NSComponent::pPhysics other) {
		}

		void CGrenade::OnCollisionExit(NSComponent::pPhysics other) {
		}

	}
}