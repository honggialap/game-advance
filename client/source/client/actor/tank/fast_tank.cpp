#include "client/actor/tank/fast_tank.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {

		pFastTank CFastTank::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
		) {
			if (world->dictionary.find(name) != world->dictionary.end()) {
				return nullptr;
			}

			uint32_t id = world->game_object_id++;
			world->game_objects[id] = std::make_unique<CFastTank>(game, world, id, name);
			world->dictionary[name] = id;

			return static_cast<pFastTank>(world->game_objects[id].get());
		}

		CFastTank::CFastTank(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSCore::CGameObject(game, world)
			, NSEngine::NSActor::CFastTank(game, world, id, name) {
		}

		CFastTank::~CFastTank() {
		}

		void CFastTank::Update(float elapsed) {
			b2Vec2 current_movement(
				speed * movement.x / 30.0f,
				speed * movement.y / 30.0f
			);
			body->SetLinearVelocity(current_movement);
		}

		void CFastTank::Render(sf::RenderWindow& window) {
			sf::Sprite& sprite = tank_sprites[1001];

			if (true) {
				float render_x = 0.0f;
				float render_y = 0.0f;
				GetPosition(render_x, render_y);

				sprite.setPosition(
					render_x,
					-render_y + window.getSize().y
				);
			}
			else {
				uint32_t latest_tick = world->latest_tick;
				uint32_t server_tick = client_world->GetServerTick();
				uint32_t tick_per_game_state = world->tick_per_game_state;

				float interval = (float(latest_tick) - float(server_tick) - float(tick_per_game_state)) / float(tick_per_game_state);

				float render_x = 0.0f;
				float render_y = 0.0f;
				GetInterpolation(render_x, render_y, interval);

				sprite.setPosition(
					render_x,
					-render_y + window.getSize().y
				);
			}

			window.draw(sprite);
		}

	}
}
