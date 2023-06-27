#include "engine/actor/creep_tank.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CCreepTankRecord::CCreepTankRecord(
			uint32_t id
		)
			: NSCore::CRecord(id)
			, position_x(0.0f), position_y(0.0f)
			, velocity_x(0.0f), velocity_y(0.0f) {
			actor_type = EActorType::CREEP_TANK;
		}

		CCreepTankRecord::CCreepTankRecord(
			uint32_t id
			, float position_x, float position_y
			, float velocity_x, float velocity_y
		)
			: NSCore::CRecord(id)
			, position_x(position_x), position_y(position_y)
			, velocity_x(velocity_x), velocity_y(velocity_y) {
			actor_type = EActorType::CREEP_TANK;
		}

		CCreepTank::CCreepTank(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world, id, name)
			, NSComponent::CPhysics(world->GetPhysics()) {
			type = EActorType::CREEP_TANK;
		}

		CCreepTank::~CCreepTank() {
		}

		void CCreepTank::LoadResource() {
			std::ifstream data_file(resource_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

			texture.loadFromFile("data/resources/textures/sample_creep1.png");
			sprite.setTexture(texture);
			sprite.setOrigin(32, 32);
		}

		void CCreepTank::UnloadResource() {
		}

		void CCreepTank::Serialize(uint32_t tick) {
			float position_x;
			float position_y;
			GetPosition(position_x, position_y);

			float velocity_x;
			float velocity_y;
			GetVelocity(velocity_x, velocity_y);

			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CCreepTankRecord>(
					id,
					position_x, position_y,
					velocity_x, velocity_y
				)
			);
		}

		void CCreepTank::Deserialize(NSCore::pRecord record) {
			auto creep_tank_record = static_cast<pCreepTankRecord>(record);
			SetPosition(creep_tank_record->position_x, creep_tank_record->position_y);
			SetVelocity(creep_tank_record->velocity_x, creep_tank_record->velocity_y);
		}

		void CCreepTank::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto creep_tank_record = static_cast<pCreepTankRecord>(record);
			*packet << creep_tank_record->position_x;
			*packet << creep_tank_record->position_y;
			*packet << creep_tank_record->velocity_x;
			*packet << creep_tank_record->velocity_y;
		}

		NSCore::pRecord CCreepTank::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CCreepTankRecord(id);

			*packet >> record->position_x;
			*packet >> record->position_y;
			*packet >> record->velocity_x;
			*packet >> record->velocity_y;

			return record;
		}

		void CCreepTank::ExecuteCommand(NSCore::pCommand command) {

		}

		void CCreepTank::Update(float elapsed) {
		}

		void CCreepTank::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CCreepTank::OnCollisionEnter(NSComponent::pPhysics other) {
		}

		void CCreepTank::OnCollisionExit(NSComponent::pPhysics other) {
		}

	}
}