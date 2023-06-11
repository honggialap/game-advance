#include "client/actor/headquarter.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {

		pHeadquarter CHeadquarter::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
		) {
			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CHeadquarter>(game, world, id, name);
			world->dictionary[name] = id;

			pHeadquarter headquarter = static_cast<pHeadquarter>(world->game_objects[id].get());
			return headquarter;
		}

		CHeadquarter::CHeadquarter(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSActor::CHeadquarter(game, world, id, name)
			, NSClient::NSCore::CGameObject(game, world) {
		}

		CHeadquarter::~CHeadquarter() {
		}

		void CHeadquarter::Load(std::string data_path) {
			NSEngine::NSActor::CHeadquarter::Load(data_path);
		}

		void CHeadquarter::Unload() {
			NSEngine::NSActor::CHeadquarter::Unload();
		}

		void CHeadquarter::Update(float elapsed) {
		}

		void CHeadquarter::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CHeadquarter::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CHeadquarter::OnCollisionEnter(other);
		}

		void CHeadquarter::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CHeadquarter::OnCollisionExit(other);
		}

	}
}
