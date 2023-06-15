#include "engine/actor/player_bullet.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CPlayerBulletRecord::CPlayerBulletRecord(
			uint32_t id
		)
			: NSCore::CRecord(id)
			, position_x(0.0f), position_y(0.0f)
			, velocity_x(0.0f), velocity_y(0.0f) {
			actor_type = EActorType::PLAYER_BULLET;
		}

		CPlayerBulletRecord::CPlayerBulletRecord(
			uint32_t id
			, float position_x, float position_y
			, float velocity_x, float velocity_y
		)
			: NSCore::CRecord(id)
			, position_x(position_x), position_y(position_y)
			, velocity_x(velocity_x), velocity_y(velocity_y) {
			actor_type = EActorType::PLAYER_BULLET;
		}

		CPlayerBullet::CPlayerBullet(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world, id, name)
			, NSComponent::CPhysics(world->GetPhysics()) {
			type = EActorType::PLAYER_BULLET;
		}

		CPlayerBullet::~CPlayerBullet() {
		}

		void CPlayerBullet::LoadResource() {
			std::ifstream data_file(resource_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

			texture.loadFromFile("data/resources/textures/sample_bullet1.png");
			sprite.setTexture(texture);
			sprite.setOrigin(16, 16);
		}

		void CPlayerBullet::UnloadResource() {
		}

		void CPlayerBullet::Serialize(uint32_t tick) {
			float position_x, position_y;
			GetPosition(position_x, position_y);

			float velocity_x, velocity_y;
			GetVelocity(velocity_x, velocity_y);

			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CPlayerBulletRecord>(
					id,
					position_x, position_y,
					velocity_x, velocity_y
				)
			);
		}

		void CPlayerBullet::Deserialize(NSCore::pRecord record) {
			auto player_bullet = static_cast<pPlayerBulletRecord>(record);
			SetPosition(player_bullet->position_x, player_bullet->position_y);
			SetVelocity(player_bullet->velocity_x, player_bullet->velocity_y);
		}

		void CPlayerBullet::PackRecord(
			NSNetworks::CPacket* packet
			, NSCore::pRecord record
		) {
			auto player_bullet_record = static_cast<pPlayerBulletRecord>(record);
			//*packet << factory_record->a;
		}

		NSCore::pRecord CPlayerBullet::UnpackRecord(
			NSNetworks::CPacket* packet
		) {
			auto record = new CPlayerBulletRecord(id);

			//*packet >> factory_record->a;

			return record;
		}

		void CPlayerBullet::Update(float elapsed) {
		}

		void CPlayerBullet::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CPlayerBullet::OnCollisionEnter(NSComponent::pPhysics other) {
		}

		void CPlayerBullet::OnCollisionExit(NSComponent::pPhysics other) {
		}

		void CPlayerBullet::PackNetworksLoadPacket(NSNetworks::CPacket* packet) {
			PackLoadPhysics(packet);
			PackLoadResource(packet);
		}

		void CPlayerBullet::UnpackNetworksLoadPacket(NSNetworks::CPacket* packet) {
			UnpackLoadPhysics(packet);
			UnpackLoadResource(packet);
		}

	}
}