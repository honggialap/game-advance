#include "server/actor/player_bullet.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pPlayerBullet CPlayerBullet::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("name");
			world->game_objects[id] = std::make_unique<CPlayerBullet>(game, world, id, name);
			world->dictionary[name] = id;

			pPlayerBullet player_bullet = static_cast<pPlayerBullet>(world->game_objects[id].get());

			auto& physics_data = data.at("physics");
			player_bullet->CreatePhysics(physics_data);

			std::string resource_path = data.at("resource_path");
			player_bullet->SetResourcePath(resource_path);

			player_bullet->Load(resource_path);

			return player_bullet;
		}

		CPlayerBullet::CPlayerBullet(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSActor::CPlayerBullet(game, world, id, name)
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