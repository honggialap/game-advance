#include "engine/actor/power_up/shovel.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CShovelRecord::CShovelRecord(uint32_t id)
			: NSCore::CRecord(id) {
			actor_type = EActorType::SHOVEL;
		}

		CShovel::CShovel(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSActor::CBasePowerUp(game, world, id, name)
		{
			type = EActorType::SHOVEL;
		}

		CShovel::~CShovel() {
		}

		void CShovel::Serialize(uint32_t tick) {
			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CShovelRecord>(
					id
				)
			);
		}

		void CShovel::Deserialize(NSCore::pRecord record) {
			auto shovel_record = static_cast<pShovelRecord>(record);
		}

		void CShovel::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto shovel_record = static_cast<pShovelRecord>(record);
			//*packet << factory_record->a;
		}

		NSCore::pRecord CShovel::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CShovelRecord(id);

			//*packet >> factory_record->a;

			return record;
		}

		void CShovel::Update(float elapsed) {
		}

		void CShovel::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CShovel::OnCollisionEnter(NSComponent::pPhysics other) {
		}

		void CShovel::OnCollisionExit(NSComponent::pPhysics other) {
		}

	}
}