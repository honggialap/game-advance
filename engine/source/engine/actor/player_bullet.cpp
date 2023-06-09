#include "engine/actor/player_bullet.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CPlayerBulletRecord::CPlayerBulletRecord(
			uint32_t id
			, float position_x, float position_y
			, float velocity_x, float velocity_y
		)
			: NSEngine::NSCore::CRecord(id)
			, position_x(position_x), position_y(position_y)
			, velocity_x(velocity_x), velocity_y(velocity_y) {
			actor_type = EActorType::PLAYER_BULLET;
		}

		CPlayerBullet::CPlayerBullet(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
		)
			: NSEngine::NSCore::CGameObject(game, world) {
			type = EActorType::PLAYER_BULLET;
		}

		CPlayerBullet::~CPlayerBullet() {
		}

		void CPlayerBullet::Load(std::string data_path) {
			//std::ifstream data_file(data_path);
			//nlohmann::json data = nlohmann::json::parse(data_file);

			texture.loadFromFile("data/resources/textures/sample_bullet1.png");
			sprite.setTexture(texture);
			sprite.setOrigin(16, 16);

			body_def.type = b2_dynamicBody;
			body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

			body = world->GetPhysics()->CreateBody(&body_def);

			collider.SetAsBox(16.0f / 30, 16.0f / 30);

			fixture_def.shape = &collider;
			fixture_def.density = 100.0f;
			fixture_def.friction = 0.0f;

			fixture_def.filter.categoryBits = ECollisionFilter::FILTER_BULLET;
			fixture_def.filter.maskBits
				= ECollisionFilter::FILTER_PLAYER_TANK
				| ECollisionFilter::FILTER_CREEP_TANK
				| ECollisionFilter::FILTER_BULLET
				| ECollisionFilter::FILTER_STRUCTURE
				| ECollisionFilter::FILTER_WALL
				//| ECollisionFilter::FILTER_WATER
				//| ECollisionFilter::FILTER_TREE
				//| ECollisionFilter::FILTER_PICK_UP
				;

			fixture = body->CreateFixture(&fixture_def);
		}

		void CPlayerBullet::Unload() {
			if (body != nullptr) {
				if (fixture != nullptr) {
					body->DestroyFixture(fixture);
					fixture = nullptr;
				}
				world->GetPhysics()->DestroyBody(body);
				body = nullptr;
			}
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

		void CPlayerBullet::Deserialize(NSEngine::NSCore::pRecord record) {
			auto player_bullet = static_cast<pPlayerBulletRecord>(record);
			SetPosition(player_bullet->position_x, player_bullet->position_y);
			SetVelocity(player_bullet->velocity_x, player_bullet->velocity_y);
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

		void CPlayerBullet::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
		}

		void CPlayerBullet::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
		}

	}
}