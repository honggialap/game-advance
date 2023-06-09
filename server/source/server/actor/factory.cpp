#include "server/actor/factory.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pFactory CFactory::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, std::string data_path
		) {
			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CFactory>(game, world);
			world->dictionary[name] = id;
			pFactory factory = static_cast<pFactory>(world->game_objects[id].get());

			factory->SetId(id);
			factory->SetName(name);
			factory->SetResourcePath(data_path);
			factory->Load(data_path);

			return factory;
		}

		CFactory::CFactory(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
		)
			: NSEngine::NSActor::CFactory(game, world)
			, NSServer::NSCore::CGameObject(game, world) {
		}

		CFactory::~CFactory() {
		}

		void CFactory::Load(std::string data_path) {
			NSEngine::NSActor::CFactory::Load(data_path);
		}

		void CFactory::Unload() {
			NSEngine::NSActor::CFactory::Unload();
		}

		void CFactory::Update(float elapsed) {
		}

		void CFactory::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CFactory::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CFactory::OnCollisionEnter(other);
		}

		void CFactory::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CFactory::OnCollisionExit(other);
		}

	}
}
