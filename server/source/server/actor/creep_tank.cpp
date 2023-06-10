#include "server/actor/creep_tank.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSActor {

		pCreepTank CCreepTank::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, nlohmann::json& data
		) {
			uint32_t id = world->game_object_id++;
			std::string name = data.at("name");

			world->game_objects[id] = std::make_unique<CCreepTank>(game, world, id, name);
			world->dictionary[name] = id;
			pCreepTank creep_tank = static_cast<pCreepTank>(world->game_objects[id].get());

			std::string resource_path = data.at("resource_path");
			creep_tank->SetResourcePath(resource_path);
			creep_tank->Load(resource_path);

			return creep_tank;
		}

		CCreepTank::CCreepTank(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSActor::CCreepTank(game, world, id, name)
			, NSServer::NSCore::CGameObject(game, world) {
		}

		CCreepTank::~CCreepTank() {
		}

		void CCreepTank::Load(std::string data_path) {
			NSEngine::NSActor::CCreepTank::Load(data_path);
		}

		void CCreepTank::Unload() {
			NSEngine::NSActor::CCreepTank::Unload();
		}

		void CCreepTank::Update(float elapsed) {
		}

		void CCreepTank::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CCreepTank::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CCreepTank::OnCollisionEnter(other);
		}

		void CCreepTank::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CCreepTank::OnCollisionExit(other);
		}

	}
}
