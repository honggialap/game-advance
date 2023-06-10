#include "server/actor/repair_kit.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pRepairKit CRepairKit::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("name");

			world->game_objects[id] = std::make_unique<CRepairKit>(game, world, id, name);
			world->dictionary[name] = id;
			pRepairKit repair_kit = static_cast<pRepairKit>(world->game_objects[id].get());

			std::string resource_path = data.at("resource_path");
			repair_kit->SetResourcePath(resource_path);
			repair_kit->Load(resource_path);

			return repair_kit;
		}

		CRepairKit::CRepairKit(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSActor::CRepairKit(game, world, id, name)
			, NSServer::NSCore::CGameObject(game, world) {
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
			NSEngine::NSActor::CRepairKit::OnCollisionEnter(other);
		}

	}
}
