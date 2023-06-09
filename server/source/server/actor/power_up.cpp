#include "server/actor/power_up.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pPowerUp CPowerUp::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, std::string data_path
		) {
			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CPowerUp>(game, world);
			world->dictionary[name] = id;
			pPowerUp power_up = static_cast<pPowerUp>(world->game_objects[id].get());

			power_up->SetId(id);
			power_up->SetName(name);
			power_up->SetResourcePath(data_path);
			power_up->Load(data_path);

			return power_up;
		}

		CPowerUp::CPowerUp(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
		)
			: NSEngine::NSActor::CPowerUp(game, world)
			, NSServer::NSCore::CGameObject(game, world) {
		}

		CPowerUp::~CPowerUp() {
		}

		void CPowerUp::Load(std::string data_path) {
			NSEngine::NSActor::CPowerUp::Load(data_path);
		}

		void CPowerUp::Unload() {
			NSEngine::NSActor::CPowerUp::Unload();
		}

		void CPowerUp::Update(float elapsed) {
		}

		void CPowerUp::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CPowerUp::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CPowerUp::OnCollisionEnter(other);
		}

		void CPowerUp::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CPowerUp::OnCollisionExit(other);
		}

	}
}