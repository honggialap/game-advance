#include "server/actor/tree.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pTree CTree::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, std::string data_path
		) {
			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CTree>(game, world);
			world->dictionary[name] = id;
			pTree tree = static_cast<pTree>(world->game_objects[id].get());

			tree->SetId(id);
			tree->SetName(name);
			tree->SetResourcePath(data_path);
			tree->Load(data_path);

			return tree;
		}

		CTree::CTree(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
		)
			: NSEngine::NSActor::CTree(game, world)
			, NSServer::NSCore::CGameObject(game, world) {
		}

		CTree::~CTree() {
		}

		void CTree::Load(std::string data_path) {
			NSEngine::NSActor::CTree::Load(data_path);
		}

		void CTree::Unload() {
			NSEngine::NSActor::CTree::Unload();
		}

		void CTree::Update(float elapsed) {
		}

		void CTree::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CTree::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CTree::OnCollisionEnter(other);
		}

		void CTree::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CTree::OnCollisionExit(other);
		}

	}
}
