#include "engine/actor/power_up/star.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CStarRecord::CStarRecord(uint32_t id)
			: NSCore::CRecord(id) {
			actor_type = EActorType::STAR;
		}

		CStar::CStar(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSActor::CBasePowerUp(game, world, id, name)
		{
			type = EActorType::STAR;
		}

		CStar::~CStar() {
		}

		void CStar::Serialize(uint32_t tick) {
			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CStarRecord>(
					id
				)
			);
		}

		void CStar::Deserialize(NSCore::pRecord record) {
			auto star_record = static_cast<pStarRecord>(record);
		}

		void CStar::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto star_record = static_cast<pStarRecord>(record);
			//*packet << factory_record->a;
		}

		NSCore::pRecord CStar::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CStarRecord(id);

			//*packet >> factory_record->a;

			return record;
		}

		void CStar::Update(float elapsed) {
		}

		void CStar::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CStar::OnCollisionEnter(NSComponent::pPhysics other) {
		}

		void CStar::OnCollisionExit(NSComponent::pPhysics other) {
		}

	}
}