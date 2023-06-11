#include "engine/actor/creep_bullet.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CCreepBulletRecord::CCreepBulletRecord(
			uint32_t id
		)
			: NSEngine::NSCore::CRecord(id) 
			, position_x(0.0f), position_y(0.0f)
			, velocity_x(0.0f), velocity_y(0.0f) {
			actor_type = EActorType::CREEP_BULLET;
		}

		CCreepBulletRecord::CCreepBulletRecord(
			uint32_t id,
			float position_x, float position_y,
			float velocity_x, float velocity_y
		)
			: NSEngine::NSCore::CRecord(id)
			, position_x(position_x), position_y(position_y)
			, velocity_x(velocity_x), velocity_y(velocity_y) {
			actor_type = EActorType::CREEP_BULLET;
		}

		CCreepBullet::CCreepBullet(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSCore::CGameObject(game, world, id, name) 
			, NSEngine::NSComponent::CPhysics(world->GetPhysics()) {
			type = EActorType::CREEP_BULLET;
		}

		CCreepBullet::~CCreepBullet() {
		}

		void CCreepBullet::Load(std::string data_path) {
			//std::ifstream data_file(data_path);
			//nlohmann::json data = nlohmann::json::parse(data_file);

			texture.loadFromFile("data/resources/textures/sample_bullet1.png");
			sprite.setTexture(texture);
			sprite.setOrigin(16, 16);
		}

		void CCreepBullet::Unload() {
		}

		void CCreepBullet::PackLoad(NSEngine::NSNetworks::CPacket* packet){
		}

		void CCreepBullet::UnpackLoad(NSEngine::NSNetworks::CPacket* packet) {
		}

		void CCreepBullet::Serialize(uint32_t tick) {
			float position_x, position_y;
			GetPosition(position_x, position_y);

			float velocity_x, velocity_y;
			GetVelocity(velocity_x, velocity_y);

			auto& records_container = world->records[tick];
			records_container.push_back(
				std::make_unique<CCreepBulletRecord>(
					id
					, position_x, position_y
					, velocity_x, velocity_y
				)
			);
		}

		void CCreepBullet::Deserialize(NSEngine::NSCore::pRecord record) {
			auto creep_bullet_record = static_cast<pCreepBulletRecord>(record);
			SetPosition(creep_bullet_record->position_x, creep_bullet_record->position_y);
			SetVelocity(creep_bullet_record->velocity_x, creep_bullet_record->velocity_y);
		}

		void CCreepBullet::PackRecord(
			NSEngine::NSNetworks::CPacket* packet
			, NSEngine::NSCore::pRecord record
		) {
			auto creep_bullet_record = static_cast<pCreepBulletRecord>(record);
			*packet << creep_bullet_record->position_x;
			*packet << creep_bullet_record->position_y;
			*packet << creep_bullet_record->velocity_x;
			*packet << creep_bullet_record->velocity_y;
		}

		void CCreepBullet::UnpackRecord(
			NSEngine::NSNetworks::CPacket* packet
			, NSEngine::NSCore::pRecord record
		) {
			auto creep_bullet_record = static_cast<pCreepBulletRecord>(record);
			*packet >> creep_bullet_record->position_x;
			*packet >> creep_bullet_record->position_y;
			*packet >> creep_bullet_record->velocity_x;
			*packet >> creep_bullet_record->velocity_y;
		}

		void CCreepBullet::Update(float elapsed) {
		}

		void CCreepBullet::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CCreepBullet::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
		}

		void CCreepBullet::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
		}

	}
}