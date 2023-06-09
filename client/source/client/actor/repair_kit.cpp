#include "client/actor/repair_kit.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {

		pRepairKit CRepairKit::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, std::string data_path
		) {
			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CRepairKit>(game, world);
			world->dictionary[name] = id;
			pRepairKit repair_kit = static_cast<pRepairKit>(world->game_objects[id].get());

			repair_kit->SetId(id);
			repair_kit->SetName(name);
			repair_kit->SetResourcePath(data_path);
			repair_kit->Load(data_path);

			return repair_kit;
		}

		CRepairKit::CRepairKit(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
		)
			: NSEngine::NSActor::CRepairKit(game, world)
			, NSClient::NSCore::CGameObject(game, world) {
		}

		CRepairKit::~CRepairKit() {
		}

		void CRepairKit::Load(std::string data_path) {
			NSEngine::NSActor::CRepairKit::Load(data_path);
		}

		void CRepairKit::Unload() {
			NSEngine::NSActor::CRepairKit::Unload();
		}

		void CRepairKit::Update(float elapsed) {
		}

		void CRepairKit::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CRepairKit::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CRepairKit::OnCollisionEnter(other);
		}

		void CRepairKit::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CRepairKit::OnCollisionExit(other);
		}

	}
}
