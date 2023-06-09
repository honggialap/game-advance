#include "server/actor/water.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pWater CWater::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, std::string data_path
		) {
			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CWater>(game, world);
			world->dictionary[name] = id;
			pWater water = static_cast<pWater>(world->game_objects[id].get());

			water->SetId(id);
			water->SetName(name);
			water->SetResourcePath(data_path);
			water->Load(data_path);

			return water;
		}

		CWater::CWater(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
		)
			: NSEngine::NSActor::CWater(game, world)
			, NSServer::NSCore::CGameObject(game, world) {
		}

		CWater::~CWater() {
		}

		void CWater::Load(std::string data_path) {
			NSEngine::NSActor::CWater::Load(data_path);
		}

		void CWater::Unload() {
			NSEngine::NSActor::CWater::Unload();
		}

		void CWater::Update(float elapsed) {
		}

		void CWater::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CWater::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CWater::OnCollisionEnter(other);
		}

		void CWater::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CWater::OnCollisionExit(other);
		}

	}
}
