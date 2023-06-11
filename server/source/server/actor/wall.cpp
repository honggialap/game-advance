#include "server/actor/wall.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pWall CWall::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("name");
			world->game_objects[id] = std::make_unique<CWall>(game, world, id, name);
			world->dictionary[name] = id;

			pWall wall = static_cast<pWall>(world->game_objects[id].get());

			auto& physics_data = data.at("physics");
			wall->CreatePhysics(physics_data);

			std::string resource_path = data.at("resource_path");
			wall->SetResourcePath(resource_path);

			wall->Load(resource_path);

			return wall;
		}

		CWall::CWall(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSActor::CWall(game, world, id, name)
			, NSServer::NSCore::CGameObject(game, world) {
		}

		CWall::~CWall() {
		}

		void CWall::Load(std::string data_path) {
			NSEngine::NSActor::CWall::Load(data_path);
		}

		void CWall::Unload() {
			NSEngine::NSActor::CWall::Unload();
		}

		void CWall::Update(float elapsed) {
		}

		void CWall::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CWall::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CWall::OnCollisionEnter(other);
		}

		void CWall::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CWall::OnCollisionExit(other);
		}

	}
}
