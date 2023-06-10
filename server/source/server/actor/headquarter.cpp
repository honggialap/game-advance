#include "server/actor/headquarter.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pHeadquarter CHeadquarter::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("data");

			world->game_objects[id] = std::make_unique<CHeadquarter>(game, world, id, name);
			world->dictionary[name] = id;
			pHeadquarter headquarter = static_cast<pHeadquarter>(world->game_objects[id].get());

			std::string resource_path = data.at("resource_path");
			headquarter->SetResourcePath(resource_path);
			
			headquarter->Load(resource_path);

			return headquarter;
		}

		CHeadquarter::CHeadquarter(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSActor::CHeadquarter(game, world, id, name)
			, NSServer::NSCore::CGameObject(game, world) {
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