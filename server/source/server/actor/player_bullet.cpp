#include "server/actor/player_bullet.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pPlayerBullet CPlayerBullet::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, std::string data_path
		) {
			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CPlayerBullet>(game, world);
			world->dictionary[name] = id;
			pPlayerBullet player_bullet = static_cast<pPlayerBullet>(world->game_objects[id].get());

			player_bullet->SetId(id);
			player_bullet->SetName(name);
			player_bullet->SetResourcePath(data_path);
			player_bullet->Load(data_path);

			return player_bullet;
		}

		CPlayerBullet::CPlayerBullet(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
		)
			: NSEngine::NSActor::CPlayerBullet(game, world)
			, NSServer::NSCore::CGameObject(game, world) {
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