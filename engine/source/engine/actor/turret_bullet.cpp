#include "engine/actor/turret_bullet.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CTurretBulletRecord::CTurretBulletRecord(
			uint32_t id
		) : NSCore::CRecord(id)
			, position_x(0.0f), position_y(0.0f)
			, velocity_x(0.0f), velocity_y(0.0f) {
			actor_type = EActorType::TURRET_BULLET;
		}

		CTurretBulletRecord::CTurretBulletRecord(
			uint32_t id
			, float position_x, float position_y
			, float velocity_x, float velocity_y
		) : NSCore::CRecord(id)
			, position_x(position_x), position_y(position_y)
			, velocity_x(velocity_x), velocity_y(velocity_y) {
			actor_type = EActorType::TURRET_BULLET;
		}

		CTurretBullet::CTurretBullet(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world, id, name) 
			, NSComponent::CPhysics(world->GetPhysics()) {
			type = EActorType::TURRET_BULLET;
		}

		CTurretBullet::~CTurretBullet() {
		}

		void CTurretBullet::LoadResource() {
			std::ifstream data_file(resource_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

			texture.loadFromFile("data/resources/textures/sample_bullet1.png");
			sprite.setTexture(texture);
			sprite.setOrigin(32, 32);
		}

		void CTurretBullet::UnloadResource() {
		}

		void CTurretBullet::Serialize(uint32_t tick) {
			float position_x, position_y;
			GetPosition(position_x, position_y);

			float velocity_x, velocity_y;
			GetVelocity(velocity_x, velocity_y);

			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CTurretBulletRecord>(
					id,
					position_x, position_y,
					velocity_x, velocity_y
				)
			);
		}

		void CTurretBullet::Deserialize(NSEngine::NSCore::pRecord record) {
			auto turret_bullet_record = static_cast<pTurretBulletRecord>(record);
			SetPosition(turret_bullet_record->position_x, turret_bullet_record->position_y);
			SetVelocity(turret_bullet_record->velocity_x, turret_bullet_record->velocity_y);
		}

		void CTurretBullet::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto turret_bullet_record = static_cast<pTurretBulletRecord>(record);
			//*packet << factory_record->a;
		}

		NSCore::pRecord CTurretBullet::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CTurretBulletRecord(id);

			//*packet >> factory_record->a;

			return record;
		}

		void CTurretBullet::Update(float elapsed) {
		}

		void CTurretBullet::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CTurretBullet::OnCollisionEnter(NSComponent::pPhysics other) {
		}

		void CTurretBullet::OnCollisionExit(NSComponent::pPhysics other) {
		}

		void CTurretBullet::PackNetworksLoadPacket(NSNetworks::CPacket* packet) {
			PackLoadPhysics(packet);
			PackLoadResource(packet);
		}

		void CTurretBullet::UnpackNetworksLoadPacket(NSNetworks::CPacket* packet) {
			UnpackLoadPhysics(packet);
			UnpackLoadResource(packet);
		}

	}
}
