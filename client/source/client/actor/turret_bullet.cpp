#include "client/actor/turret_bullet.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {

		pTurretBullet CTurretBullet::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, std::string data_path
		) {
			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CTurretBullet>(game, world);
			world->dictionary[name] = id;
			pTurretBullet turret_bullet = static_cast<pTurretBullet>(world->game_objects[id].get());

			turret_bullet->SetId(id);
			turret_bullet->SetName(name);
			turret_bullet->SetResourcePath(data_path);
			turret_bullet->Load(data_path);

			return turret_bullet;
		}

		CTurretBullet::CTurretBullet(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
		)
			: NSEngine::NSActor::CTurretBullet(game, world)
			, NSClient::NSCore::CGameObject(game, world) {
		}

		CTurretBullet::~CTurretBullet() {
		}

		void CTurretBullet::Load(std::string data_path) {
			NSEngine::NSActor::CTurretBullet::Load(data_path);
		}

		void CTurretBullet::Unload() {
			NSEngine::NSActor::CTurretBullet::Unload();
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

		void CTurretBullet::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CTurretBullet::OnCollisionEnter(other);
		}

		void CTurretBullet::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CTurretBullet::OnCollisionExit(other);
		}

	}
}
