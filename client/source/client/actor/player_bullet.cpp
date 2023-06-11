#include "client/actor/player_bullet.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {

		pPlayerBullet CPlayerBullet::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
		) {
			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CPlayerBullet>(game, world, id, name);
			world->dictionary[name] = id;

			pPlayerBullet player_bullet = static_cast<pPlayerBullet>(world->game_objects[id].get());
			return player_bullet;
		}

		CPlayerBullet::CPlayerBullet(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSActor::CPlayerBullet(game, world, id, name)
			, NSClient::NSCore::CGameObject(game, world) {
		}

		CPlayerBullet::~CPlayerBullet() {
		}

		void CPlayerBullet::Load(std::string data_path) {
			NSEngine::NSActor::CPlayerBullet::Load(data_path);
		}

		void CPlayerBullet::Unload() {
			NSEngine::NSActor::CPlayerBullet::Unload();
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
			NSEngine::NSActor::CPlayerBullet::OnCollisionEnter(other);
		}

		void CPlayerBullet::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CPlayerBullet::OnCollisionExit(other);
		}

	}
}
