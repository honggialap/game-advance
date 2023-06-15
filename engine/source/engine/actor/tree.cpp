#include "engine/actor/tree.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CTree::CTree(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world, id, name)
			, NSComponent::CPhysics(world->GetPhysics()) {
			type = EActorType::TREE;
		}

		CTree::~CTree() {
		}

		void CTree::LoadResource() {
			std::ifstream data_file(resource_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

			texture.loadFromFile("data/resources/textures/sample_tree.png");
			sprite.setTexture(texture);
			sprite.setOrigin(32, 32);
		}

		void CTree::UnloadResource() {
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

		void CTree::OnCollisionEnter(NSComponent::pPhysics other) {
		}

		void CTree::OnCollisionExit(NSComponent::pPhysics other) {
		}

		void CTree::PackNetworksLoadPacket(NSNetworks::CPacket* packet) {
			PackLoadPhysics(packet);
			PackLoadResource(packet);
		}

		void CTree::UnpackNetworksLoadPacket(NSNetworks::CPacket* packet) {
			UnpackLoadPhysics(packet);
			UnpackLoadResource(packet);
		}

	}
}
