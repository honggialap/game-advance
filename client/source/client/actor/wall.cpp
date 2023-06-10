#include "client/actor/wall.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {

		pWall CWall::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, std::string data_path
		) {
			uint32_t id = world->game_object_id++;

			world->game_objects[id] = std::make_unique<CWall>(game, world, id, name);
			world->dictionary[name] = id;
			pWall wall = static_cast<pWall>(world->game_objects[id].get());

			wall->SetResourcePath(data_path);
			wall->Load(data_path);

			return wall;
		}

		CWall::CWall(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSActor::CWall(game, world, id, name)
			, NSClient::NSCore::CGameObject(game, world) {
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
