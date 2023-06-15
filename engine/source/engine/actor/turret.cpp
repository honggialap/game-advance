#include "engine/actor/turret.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CTurretRecord::CTurretRecord(uint32_t id)
			: NSCore::CRecord(id) {
			actor_type = EActorType::TURRET;
		}

		CTurret::CTurret(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world, id, name) 
			, NSComponent::CPhysics(world->GetPhysics()) {
			type = EActorType::TURRET;
		}

		CTurret::~CTurret() {
		}

		void CTurret::LoadResource() {
			std::ifstream data_file(resource_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

			texture.loadFromFile("data/resources/textures/sample_turret1.png");
			sprite.setTexture(texture);
			sprite.setOrigin(32, 32);
		}

		void CTurret::UnloadResource() {
		}

		void CTurret::Serialize(uint32_t tick) {
			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CTurretRecord>(
					id
				)
			);
		}

		void CTurret::Deserialize(NSCore::pRecord record) {
			auto turret_record = static_cast<pTurretRecord>(record);
		}

		void CTurret::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto turret_record = static_cast<pTurretRecord>(record);
			//*packet << factory_record->a;
		}

		NSCore::pRecord CTurret::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CTurretRecord(id);

			//*packet >> factory_record->a;

			return record;
		}

		void CTurret::ExecuteCommand(NSCore::pCommand command) {
		}

		void CTurret::Update(float elapsed) {
		}

		void CTurret::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CTurret::OnCollisionEnter(NSComponent::pPhysics other) {
		}

		void CTurret::OnCollisionExit(NSComponent::pPhysics other) {
		}

		void CTurret::PackNetworksLoadPacket(NSNetworks::CPacket* packet) {
			PackLoadPhysics(packet);
			PackLoadResource(packet);
		}

		void CTurret::UnpackNetworksLoadPacket(NSNetworks::CPacket* packet) {
			UnpackLoadPhysics(packet);
			UnpackLoadResource(packet);
		}

	}
}
