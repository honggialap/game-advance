#include "engine/actor/power_up.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CPowerUpRecord::CPowerUpRecord(
			uint32_t id
		)
			: NSCore::CRecord(id)
			, position_x(0.0f), position_y(0.0f) {
			actor_type = EActorType::POWER_UP;
		}

		CPowerUpRecord::CPowerUpRecord(
			uint32_t id
			, float position_x, float position_y
		)
			: NSCore::CRecord(id)
			, position_x(position_x), position_y(position_y) {
			actor_type = EActorType::POWER_UP;
		}

		CPowerUp::CPowerUp(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world, id, name)
			, NSComponent::CPhysics(world->GetPhysics()) {
			type = EActorType::POWER_UP;
		}

		CPowerUp::~CPowerUp() {
		}

		void CPowerUp::LoadResource() {
			std::ifstream data_file(resource_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

			texture.loadFromFile("data/resources/textures/sample_power_up.png");
			sprite.setTexture(texture);
			sprite.setOrigin(32, 32);
		}

		void CPowerUp::UnloadResource() {
		}

		void CPowerUp::Serialize(uint32_t tick) {
			float position_x, position_y;
			GetPosition(position_x, position_y);

			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CPowerUpRecord>(
					id,
					position_x, position_y
				)
			);
		}

		void CPowerUp::Deserialize(NSCore::pRecord record) {
			auto power_up_record = static_cast<pPowerUpRecord>(record);
			SetPosition(power_up_record->position_x, power_up_record->position_y);
		}

		void CPowerUp::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto power_up_record = static_cast<pPowerUpRecord>(record);
			//*packet << factory_record->a;
		}

		NSCore::pRecord CPowerUp::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CPowerUpRecord(id);

			//*packet >> factory_record->a;

			return record;
		}

		void CPowerUp::Update(float elapsed) {
		}

		void CPowerUp::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CPowerUp::OnCollisionEnter(NSComponent::pPhysics other) {
		}

		void CPowerUp::OnCollisionExit(NSComponent::pPhysics other) {
		}

		void CPowerUp::PackNetworksLoadPacket(NSNetworks::CPacket* packet) {
			PackLoadPhysics(packet);
			PackLoadResource(packet);
		}

		void CPowerUp::UnpackNetworksLoadPacket(NSNetworks::CPacket* packet) {
			UnpackLoadPhysics(packet);
			UnpackLoadResource(packet);
		}

	}
}
