#include "engine/actor/power_up/tank.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CTankRecord::CTankRecord(uint32_t id)
			: NSCore::CRecord(id) {
			actor_type = EActorType::TANK;
		}

		CTank::CTank(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSActor::CBasePowerUp(game, world, id, name)
		{
			type = EActorType::TANK;
		}

		CTank::~CTank() {
		}

		void CTank::Serialize(uint32_t tick) {
			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CTankRecord>(
					id
				)
			);
		}

		void CTank::Deserialize(NSCore::pRecord record) {
			auto tank_record = static_cast<pTankRecord>(record);
		}

		void CTank::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto tank_record = static_cast<pTankRecord>(record);
			//*packet << factory_record->a;
		}

		NSCore::pRecord CTank::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CTankRecord(id);

			//*packet >> factory_record->a;

			return record;
		}

		void CTank::Update(float elapsed) {
		}

		void CTank::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CTank::OnCollisionEnter(NSComponent::pPhysics other) {
		}

		void CTank::OnCollisionExit(NSComponent::pPhysics other) {
		}

	}
}