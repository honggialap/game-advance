#include "engine/actor/repair_kit.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CRepairKitRecord::CRepairKitRecord(
			uint32_t id
		)
			: NSCore::CRecord(id)
			, position_x(0.0f), position_y(0.0f) {
			actor_type = EActorType::REPAIR_KIT;
		}

		CRepairKitRecord::CRepairKitRecord(
			uint32_t id
			, float position_x, float position_y
		)
			: NSCore::CRecord(id)
			, position_x(position_x), position_y(position_y) {
			actor_type = EActorType::REPAIR_KIT;
		}


		CRepairKit::CRepairKit(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world, id, name)
			, NSComponent::CPhysics(world->GetPhysics()) {
			type = EActorType::REPAIR_KIT;
		}

		CRepairKit::~CRepairKit() {
		}

		void CRepairKit::LoadResource() {
			std::ifstream data_file(resource_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

			texture.loadFromFile("data/resources/textures/sample_repair_kit.png");
			sprite.setTexture(texture);
			sprite.setOrigin(32, 32);
		}

		void CRepairKit::UnloadResource() {
		}

		void CRepairKit::Serialize(uint32_t tick) {
			float position_x, position_y;
			GetPosition(position_x, position_y);

			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CRepairKitRecord>(
					id,
					position_x, position_y
				)
			);
		}

		void CRepairKit::Deserialize(NSEngine::NSCore::pRecord record) {
			auto repair_kit_record = static_cast<pRepairKitRecord>(record);
			SetPosition(repair_kit_record->position_x, repair_kit_record->position_y);
		}

		void CRepairKit::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto repair_kit_record = static_cast<pRepairKitRecord>(record);
			//*packet << factory_record->a;
		}

		NSCore::pRecord CRepairKit::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CRepairKitRecord(id);

			//*packet >> factory_record->a;

			return record;
		}

		void CRepairKit::Update(float elapsed) {
		}

		void CRepairKit::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CRepairKit::OnCollisionEnter(NSComponent::pPhysics other) {
		}

		void CRepairKit::OnCollisionExit(NSComponent::pPhysics other) {
		}

	}
}
