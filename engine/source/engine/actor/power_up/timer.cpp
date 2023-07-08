#include "engine/actor/power_up/timer.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CTimerRecord::CTimerRecord(uint32_t id)
			: NSCore::CRecord(id) {
			actor_type = EActorType::TIMER;
		}

		CTimer::CTimer(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSActor::CBasePowerUp(game, world, id, name) 
		{
			type = EActorType::TIMER;
		}

		CTimer::~CTimer() {
		}

		void CTimer::Serialize(uint32_t tick) {
			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CTimerRecord>(
					id
				)
			);
		}

		void CTimer::Deserialize(NSCore::pRecord record) {
			auto timer_record = static_cast<pTimerRecord>(record);
		}

		void CTimer::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto timer_record = static_cast<pTimerRecord>(record);
			//*packet << factory_record->a;
		}

		NSCore::pRecord CTimer::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CTimerRecord(id);

			//*packet >> factory_record->a;

			return record;
		}

		void CTimer::Update(float elapsed) {
		}

		void CTimer::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CTimer::OnCollisionEnter(NSComponent::pPhysics other) {
		}

		void CTimer::OnCollisionExit(NSComponent::pPhysics other) {
		}

	}
}