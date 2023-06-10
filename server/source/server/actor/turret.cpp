#include "server/actor/turret.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pTurret CTurret::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("name");

			world->game_objects[id] = std::make_unique<CTurret>(game, world, id, name);
			world->dictionary[name] = id;
			pTurret turret = static_cast<pTurret>(world->game_objects[id].get());

			std::string resource_path = data.at("resource_path");
			turret->SetResourcePath(resource_path);

			turret->Load(resource_path);

			return turret;
		}

		CTurret::CTurret(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSActor::CTurret(game, world, id, name)
			, NSServer::NSCore::CGameObject(game, world) {
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
