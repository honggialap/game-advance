#include "engine/actor/power_up/helmet.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CHelmetRecord::CHelmetRecord(uint32_t id)
			: NSCore::CRecord(id) {
			actor_type = EActorType::HELMET;
		}

		CHelmet::CHelmet(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSActor::CBasePowerUp(game, world, id, name)
		{
			type = EActorType::HELMET;
		}

		CHelmet::~CHelmet() {
		}

		void CHelmet::Serialize(uint32_t tick) {
			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CHelmetRecord>(
					id
				)
			);
		}

		void CHelmet::Deserialize(NSCore::pRecord record) {
			auto helmet_record = static_cast<pHelmetRecord>(record);
		}

		void CHelmet::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto helmet_record = static_cast<pHelmetRecord>(record);
			//*packet << factory_record->a;
		}

		NSCore::pRecord CHelmet::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CHelmetRecord(id);

			//*packet >> factory_record->a;

			return record;
		}

		void CHelmet::Update(float elapsed) {
		}

		void CHelmet::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CHelmet::OnCollisionEnter(NSComponent::pPhysics other) {
		}

		void CHelmet::OnCollisionExit(NSComponent::pPhysics other) {
		}

	}
}