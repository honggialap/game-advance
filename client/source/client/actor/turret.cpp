#include "client/actor/turret.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {
		
		pTurret CTurret::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, std::string data_path
		) {
			uint32_t id = world->game_object_id++;

			world->game_objects[id] = std::make_unique<CTurret>(game, world, id, name);
			world->dictionary[name] = id;
			pTurret turret = static_cast<pTurret>(world->game_objects[id].get());

			turret->SetResourcePath(data_path);
			turret->Load(data_path);

			return turret;
		}

		CTurret::CTurret(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSActor::CTurret(game, world, id, name)
			, NSClient::NSCore::CGameObject(game, world) {
		}

		CTurret::~CTurret() {
		}

		void CTurret::Load(std::string data_path) {
			NSEngine::NSActor::CTurret::Load(data_path);
		}

		void CTurret::Unload() {
			NSEngine::NSActor::CTurret::Unload();
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

		void CTurret::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CTurret::OnCollisionEnter(other);
		}

		void CTurret::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CTurret::OnCollisionExit(other);
		}

	}
}
