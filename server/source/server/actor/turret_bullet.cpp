#include "server/actor/turret_bullet.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pTurretBullet CTurretBullet::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("name");
			world->game_objects[id] = std::make_unique<CTurretBullet>(game, world, id, name);
			world->dictionary[name] = id;

			pTurretBullet turret_bullet = static_cast<pTurretBullet>(world->game_objects[id].get());

			auto& physics_data = data.at("physics");
			turret_bullet->CreatePhysics(physics_data);

			std::string resource_path = data.at("resource_path");
			turret_bullet->SetResourcePath(resource_path);
			
			turret_bullet->Load(resource_path);

			return turret_bullet;
		}

		CTurretBullet::CTurretBullet(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSActor::CTurretBullet(game, world, id, name)
			, NSServer::NSCore::CGameObject(game, world) {
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
