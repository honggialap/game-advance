#include "engine/actor/repair_kit.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CRepairKitRecord::CRepairKitRecord(
			uint32_t id
		)
			: NSEngine::NSCore::CRecord(id)
			, position_x(0.0f), position_y(0.0f) {
			actor_type = EActorType::REPAIR_KIT;
		}

		CRepairKitRecord::CRepairKitRecord(
			uint32_t id
			, float position_x, float position_y
		)
			: NSEngine::NSCore::CRecord(id)
			, position_x(position_x), position_y(position_y) {
			actor_type = EActorType::REPAIR_KIT;
		}


		CRepairKit::CRepairKit(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSCore::CGameObject(game, world, id, name)
			, NSEngine::NSComponent::CPhysics(world->GetPhysics()) {
			type = EActorType::REPAIR_KIT;
		}

		CRepairKit::~CRepairKit() {
		}

		void CRepairKit::Load(std::string data_path) {
			//std::ifstream data_file(data_path);
			//nlohmann::json data = nlohmann::json::parse(data_file);

			texture.loadFromFile("data/resources/textures/sample_repair_kit.png");
			sprite.setTexture(texture);
			sprite.setOrigin(32, 32);

			body_def.type = b2_kinematicBody;
			body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

			body = world->GetPhysics()->CreateBody(&body_def);

			collider.SetAsBox(32.0f / 30, 32.0f / 30);

			fixture_def.shape = &collider;
			fixture_def.density = 100.0f;
			fixture_def.friction = 0.0f;

			fixture_def.filter.categoryBits = ECollisionFilter::FILTER_PICK_UP;
			fixture_def.filter.maskBits
				= ECollisionFilter::FILTER_PLAYER_TANK
				//| ECollisionFilter::FILTER_CREEP_TANK
				//| ECollisionFilter::FILTER_BULLET
				//| ECollisionFilter::FILTER_STRUCTURE
				//| ECollisionFilter::FILTER_WALL
				//| ECollisionFilter::FILTER_WATER
				//| ECollisionFilter::FILTER_TREE
				//| ECollisionFilter::FILTER_PICK_UP
				;

			fixture = body->CreateFixture(&fixture_def);
		}

		void CRepairKit::Unload() {
			if (body != nullptr) {
				if (fixture != nullptr) {
					body->DestroyFixture(fixture);
					fixture = nullptr;
				}
				world->GetPhysics()->DestroyBody(body);
				body = nullptr;
			}
		}

		void CRepairKit::PackLoad(NSEngine::NSNetworks::CPacket* packet) {
		}

		void CRepairKit::UnpackLoad(NSEngine::NSNetworks::CPacket* packet) {
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
			NSEngine::NSNetworks::CPacket* packet
			, NSEngine::NSCore::pRecord record
		) {
			auto repair_kit_record = static_cast<pRepairKitRecord>(record);
			//*packet << factory_record->a;
		}

		void CRepairKit::UnpackRecord(
			NSEngine::NSNetworks::CPacket* packet
			, NSEngine::NSCore::pRecord record
		) {
			auto repair_kit_record = static_cast<pRepairKitRecord>(record);
			//*packet >> factory_record->a;
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

		void CRepairKit::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
		}

		void CRepairKit::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
		}

	}
}
