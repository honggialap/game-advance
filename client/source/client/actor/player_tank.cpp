#include "client/actor/player_tank.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSActor {

		pPlayerTank CPlayerTank::Create(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, std::string name
			, std::string data_path
		) {
			uint32_t id = world->game_object_id++;

			world->game_objects[id] = std::make_unique<CPlayerTank>(game, world, id, name);
			world->dictionary[name] = id;
			pPlayerTank player_tank = static_cast<pPlayerTank>(world->game_objects[id].get());

			player_tank->SetResourcePath(data_path);
			player_tank->Load(data_path);

			return player_tank;
		}

		CPlayerTank::CPlayerTank(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
			, uint32_t id
			, std::string name
		)
			: NSEngine::NSActor::CPlayerTank(game, world, id, name)
			, NSClient::NSCore::CGameObject(game, world) {
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
			if (is_player_controlled) {
				sf::Vector2i current_movement(0, 0);
				switch (game_client->GetPlayerId()) {
				case 1: {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
						current_movement.y = 1;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
						current_movement.y = -1;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
						current_movement.x = -1;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
						current_movement.x = 1;
					}
					break;
				}

				case 2: {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
						current_movement.y = 1;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
						current_movement.y = -1;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
						current_movement.x = -1;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
						current_movement.x = 1;
					}
					break;
				}

				case 3: {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
						current_movement.y = 1;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
						current_movement.y = -1;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
						current_movement.x = -1;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
						current_movement.x = 1;
					}
					break;
				}

				case 4: {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
						current_movement.y = 1;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
						current_movement.y = -1;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
						current_movement.x = -1;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
						current_movement.x = 1;
					}
					break;
				}

				}

				if (current_movement.x != movement.x
					|| current_movement.y != movement.y) {
					NSEngine::NSActor::CMoveCommand move_command(id, current_movement.x, current_movement.y);

					world->commands[tick].push_back(
						std::make_unique<NSEngine::NSActor::CMoveCommand>(move_command)
					);
					SendMoveCommand(tick, move_command);
				}
			}
		}

		void CPlayerTank::ExecuteCommand(NSEngine::NSCore::pCommand command) {
			switch (command->command_type) {
			case NSEngine::ECommandType::PLAYER_TANK_MOVE: {
				auto move_command = static_cast<NSEngine::NSActor::pMoveCommand>(command);
				SetMovement(move_command->x, move_command->y);
				break;
			}

			case NSEngine::ECommandType::PLAYER_TANK_SHOOT: {
				auto shoot_command = static_cast<NSEngine::NSActor::CShootCommand*>(command);
				break;
			}
			}
		}

		void CPlayerTank::Update(float elapsed) {
			b2Vec2 current_movement(
				speed * movement.x / 30.0f,
				speed * movement.y / 30.0f
			);
			body->SetLinearVelocity(current_movement);
		}

		void CPlayerTank::Render(sf::RenderWindow& window) {
			if (is_player_controlled) {
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

				float render_x = last_known_x + ((latest_x - last_known_x) * interval);
				float render_y = last_known_y + ((latest_y - last_known_y) * interval);

				sprite.setPosition(
					render_x,
					-render_y + window.getSize().y
				);
			}

			window.draw(sprite);
		}

		void CPlayerTank::OnCollisionEnter(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CPlayerTank::OnCollisionEnter(other);
		}

		void CPlayerTank::OnCollisionExit(NSEngine::NSComponent::pPhysics other) {
			NSEngine::NSActor::CPlayerTank::OnCollisionExit(other);
		}

		void CPlayerTank::SendMoveCommand(uint32_t tick, NSEngine::NSActor::CMoveCommand move_command) {
			auto move_command_packet = std::make_shared<NSEngine::NSNetworks::CPacket>(NSEngine::EPacketType::PLAYER_MOVE);
			*move_command_packet
				<< game_client->GetClientId()
				<< player_id
				<< tick
				<< move_command.game_object_id
				<< move_command.command_type
				<< move_command.x
				<< move_command.y
				;
			game_client->Send(move_command_packet);
		}

	}
}
