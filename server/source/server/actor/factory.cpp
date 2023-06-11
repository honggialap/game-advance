#include "server/actor/factory.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pFactory CFactory::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("name");
			world->game_objects[id] = std::make_unique<CFactory>(game, world, id, name);
			world->dictionary[name] = id;

			pFactory factory = static_cast<pFactory>(world->game_objects[id].get());

			auto& physics_data = data.at("physics");
			factory->CreatePhysics(physics_data);

			std::string resource_path = data.at("resource_path");
			factory->SetResourcePath(resource_path);
			
			factory->Load(resource_path);

			return factory;
		}

		CFactory::CFactory(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSActor::CFactory(game, world, id, name)
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
