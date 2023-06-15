#include "engine/actor/water.h"

#include "engine/core/game.h"
#include "engine/core/world.h"

namespace NSEngine {
	namespace NSActor {

		CWater::CWater(
			NSCore::pGame game
			, NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world, id, name) 
			, NSComponent::CPhysics(world->GetPhysics()) {
			type = EActorType::WATER;
		}

		CWater::~CWater() {
		}

		void CWater::LoadResource() {
			std::ifstream data_file(resource_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

			texture.loadFromFile("data/resources/textures/sample_water.png");
			sprite.setTexture(texture);
			sprite.setOrigin(32, 32);
		}

		void CWater::UnloadResource() {
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

		void CWater::OnCollisionEnter(NSComponent::pPhysics other) {
		}

		void CWater::OnCollisionExit(NSComponent::pPhysics other) {
		}

		void CWater::PackNetworksLoadPacket(NSNetworks::CPacket* packet) {
			PackLoadPhysics(packet);
			PackLoadResource(packet);
		}

		void CWater::UnpackNetworksLoadPacket(NSNetworks::CPacket* packet) {
			UnpackLoadPhysics(packet);
			UnpackLoadResource(packet);
		}

	}
}
