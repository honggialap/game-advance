#include "server/actor/player_tank.h"
#include "server/core/game.h"
#include "server/core/world.h"

#include "server/actor/wall.h"

namespace NSServer {
	namespace NSActor {

		pPlayerTank CPlayerTank::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, std::string data_path
		) {
			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CPlayerTank>(game, world);
			world->dictionary[name] = id;
			pPlayerTank player_tank = static_cast<pPlayerTank>(world->game_objects[id].get());

			player_tank->SetId(id);
			player_tank->SetName(name);
			player_tank->SetResourcePath(data_path);
			player_tank->Load(data_path);

			return player_tank;
		}

		CPlayerTank::CPlayerTank(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
		)
			: NSEngine::NSActor::CPlayerTank(game, world)
			, NSServer::NSCore::CGameObject(game, world) {
		}

		CPlayerTank::~CPlayerTank() {
		}

		void CPlayerTank::Load(std::string data_path) {
			NSEngine::NSActor::CPlayerTank::Load(data_path);
		}

		void CPlayerTank::Unload() {
			NSEngine::NSActor::CPlayerTank::Unload();
		}

		void CPlayerTank::HandleInput(uint32_t tick) {

		}

		void CPlayerTank::Update(float elapsed) {
			b2Vec2 current_movement(
				speed * movement.x / 30.0f,
				speed * movement.y / 30.0f
			);
			body->SetLinearVelocity(current_movement);
		}

		void CPlayerTank::Render(sf::RenderWindow& window) {
			float render_x = 0.0f;
			float render_y = 0.0f;
			GetPosition(render_x, render_y);

			sprite.setPosition(
				render_x,
				-render_y + window.getSize().y
			);

			window.draw(sprite);
		}

		void CPlayerTank::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CPlayerTank::OnCollisionEnter(other);
		}

		void CPlayerTank::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CPlayerTank::OnCollisionExit(other);
		}

	}
}