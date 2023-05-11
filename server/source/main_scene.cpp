#include "main_scene.h"
#include "game.h"

void MainScene::Load(std::string data_path) {
	std::ifstream data_file(data_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	camera.reset(sf::FloatRect(0, 0, 800, 600));
	camera.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	font.loadFromFile("data/resources/fonts/arial.ttf");
	text.setFont(font);

	for (uint32_t i = 0; i <= game->open_slots; i++) {
		worlds[i] = new World();

		auto player1_tank = static_cast<Tank*>(worlds[i]->CreateGameObject(game, ACTOR_TYPE_TANK, 100.0f, 100.0f));
		player1_tank->SetPlayerId(1);

		auto player2_tank = static_cast<Tank*>(worlds[i]->CreateGameObject(game, ACTOR_TYPE_TANK, 200.0f, 200.0f));
		player2_tank->SetPlayerId(2);

		auto player3_tank = static_cast<Tank*>(worlds[i]->CreateGameObject(game, ACTOR_TYPE_TANK, 300.0f, 300.0f));
		player3_tank->SetPlayerId(3);

		auto player4_tank = static_cast<Tank*>(worlds[i]->CreateGameObject(game, ACTOR_TYPE_TANK, 400.0f, 400.0f));
		player4_tank->SetPlayerId(4);

		if (i != 0) {
			player_ping[i] = 0;;
		}
	}
}

void MainScene::Unload() {
	for (uint32_t i = 0; i <= game->open_slots; i++) {
		delete worlds[i];
	}
	worlds.clear();
	player_ping.clear();
}

void MainScene::Update(float elapsed) {
	switch (state) {
	case MainScene::Loading:
		break;

	case MainScene::Run:

		std::vector<std::thread> client_threads;
		for (uint32_t i = 1; i <= game->open_slots; i++) {
			auto& world = worlds[i];
			uint32_t client_id = game->players[i].first;
			client_threads.emplace_back(
				[&]() {
#pragma region Client-clone
					if (world->rollback) {
						uint32_t last_tick = world->latest_tick - 1;
						uint32_t command_received_at_tick = world->rollback_tick;
						uint32_t tick_to_be_deserialize = command_received_at_tick - 1;

						for (uint32_t erasing_tick = last_tick;
							erasing_tick > tick_to_be_deserialize;
							erasing_tick--) {
							world->records.erase(erasing_tick);
						}

						auto& records_container = world->records[tick_to_be_deserialize];
						for (auto& record : records_container) {
							world->game_objects[record->game_object_id]->Deserialize(record.get());
						}

						for (uint32_t i = command_received_at_tick;
							i <= last_tick;
							i++) {

							if (world->commands.find(i) != world->commands.end()) {
								auto& commands_at_tick = world->commands.at(i);
								for (auto& command : commands_at_tick) {
									world->game_objects[
										command->game_object_id
									]->ExecuteCommand(command.get());
								}
							}

							for (auto& game_object_container : world->game_objects) {
								game_object_container.second->Update(elapsed);
							}
							world->physics_world->Step(elapsed, 8, 3);

							for (auto& game_object_container : world->game_objects) {
								game_object_container.second->Serialize(i);
							}
						}

						world->rollback = false;
						world->rollback_tick = last_tick;
					}

					for (auto& game_object_container : world->game_objects) {
						game_object_container.second->HandleInput(
							world->latest_tick
						);
					}

					if (world->commands.find(world->latest_tick) != world->commands.end()) {
						auto& commands_at_tick = world->commands.at(world->latest_tick);
						for (auto& command : commands_at_tick) {
							world->game_objects[
								command->game_object_id
							]->ExecuteCommand(command.get());
						}
					}

					for (auto& game_object_container : world->game_objects) {
						game_object_container.second->Update(elapsed);
					}
					world->physics_world->Step(elapsed, 8, 3);

					for (auto& game_object_container : world->game_objects) {
						game_object_container.second->Serialize(world->latest_tick);
					}

					if (!world->commands.empty() && world->latest_tick > 128) {
						while (
							!world->commands.empty()
							&& world->commands.begin()->first < world->latest_tick - 128
							) {
							auto erasing_tick = world->commands.begin()->first;
							world->commands.erase(erasing_tick);
						}
					}
					if (!world->records.empty() && world->latest_tick > 128) {
						while (
							!world->records.empty()
							&& world->records.begin()->first < world->latest_tick - 128
							) {
							auto erasing_tick = world->records.begin()->first;
							world->records.erase(erasing_tick);
						}
					}
				}
#pragma endregion
			);
		}
		for (auto& thread : client_threads) {
			thread.join();
		}

		auto& server_world = worlds[0];
#pragma region Server
		if (server_world->rollback) {
			uint32_t last_tick = server_world->latest_tick - 1;
			uint32_t command_received_at_tick = server_world->rollback_tick;
			uint32_t tick_to_be_deserialize = command_received_at_tick - 1;

			for (uint32_t erasing_tick = last_tick;
				erasing_tick > tick_to_be_deserialize;
				erasing_tick--) {
				server_world->records.erase(erasing_tick);
			}

			auto& records_container = server_world->records[tick_to_be_deserialize];
			for (auto& record : records_container) {
				server_world->game_objects[record->game_object_id]->Deserialize(record.get());
			}

			for (uint32_t i = command_received_at_tick;
				i <= last_tick;
				i++) {

				if (server_world->commands.find(i) != server_world->commands.end()) {
					auto& commands_at_tick = server_world->commands.at(i);
					for (auto& command : commands_at_tick) {
						server_world->game_objects[
							command->game_object_id
						]->ExecuteCommand(command.get());
					}
				}

				for (auto& game_object_container : server_world->game_objects) {
					game_object_container.second->Update(elapsed);
				}
				server_world->physics_world->Step(elapsed, 8, 3);

				for (auto& game_object_container : server_world->game_objects) {
					game_object_container.second->Serialize(i);
				}
			}

			server_world->rollback = false;
			server_world->rollback_tick = last_tick;
		}

		for (auto& game_object_container : server_world->game_objects) {
			game_object_container.second->HandleInput(
				server_world->latest_tick
			);
		}

		if (server_world->commands.find(server_world->latest_tick) != server_world->commands.end()) {
			auto& commands_at_tick = server_world->commands.at(server_world->latest_tick);
			for (auto& command : commands_at_tick) {
				server_world->game_objects[
					command->game_object_id
				]->ExecuteCommand(command.get());
			}
		}

		for (auto& game_object_container : server_world->game_objects) {
			game_object_container.second->Update(elapsed);
		}
		server_world->physics_world->Step(elapsed, 8, 3);

		for (auto& game_object_container : server_world->game_objects) {
			game_object_container.second->Serialize(server_world->latest_tick);
		}

		if (!server_world->commands.empty() && server_world->latest_tick > 128) {
			while (
				!server_world->commands.empty()
				&& server_world->commands.begin()->first < server_world->latest_tick - 128
				) {
				auto erasing_tick = server_world->commands.begin()->first;
				server_world->commands.erase(erasing_tick);
			}
		}
		if (!server_world->records.empty() && server_world->latest_tick > 128) {
			while (
				!server_world->records.empty()
				&& server_world->records.begin()->first < server_world->latest_tick - 128
				) {
				auto erasing_tick = server_world->records.begin()->first;
				server_world->records.erase(erasing_tick);
			}
		}
#pragma endregion
		
		for (uint32_t i = 1; i <= game->open_slots; i++) {
			auto& world = worlds[i];
			uint32_t client_id = game->players[i].first;
			if (world->latest_tick > default_delay_tick) {
				if (world->latest_tick % tick_per_game_state == 0) {
					SendGameStatePacket(client_id, world);
				}
			}
		}

		for (auto& world : worlds) {
			world.second->latest_tick += 1;
		}

		break;
	}
}

void MainScene::Render(sf::RenderWindow& window) {
	window.setView(camera);
	window.draw(text);

	switch (state) {
	case MainScene::Loading: {
		break;
	}

	case MainScene::Run: {
		for (auto& game_object_container : worlds[0]->game_objects) {
			game_object_container.second->Render(window);
		}
		break;
	}
	}
}

sf::View& MainScene::GetCamera() {
	return camera;
}

void MainScene::OnConnect(uint32_t connection_id) {

}

void MainScene::OnDisconnect(uint32_t connection_id) {

}

bool MainScene::ProcessPacket(std::shared_ptr<Packet> packet) {
	switch (packet->GetPacketType()) {
	case PacketType::ClientReady: {
		ready_client_count += 1;
		if (ready_client_count == game->open_slots) {
			SendLoadPacket();
		}
		return true;
	}

	case PacketType::ClientLoad: {
		load_client_count += 1;
		if (load_client_count == game->open_slots) {
			state = State::Run;
			SendStartGamePacket();
		}
		return true;
	}

	case PacketType::Ping: {
		uint32_t client_id = 0;
		uint32_t player_id = 0;
		uint32_t reply_ping_tick = 0;
		uint32_t ping = 0;

		*packet
			>> client_id
			>> player_id
			>> reply_ping_tick
			>> ping
			;

		player_ping[player_id] = ping;
		worlds[player_id]->ack_tick = reply_ping_tick;

		SendReplyPingPacket(client_id, reply_ping_tick);
		return true;
	}

	case PacketType::PlayerMove: {
		uint32_t client_id;
		uint32_t player_id;
		uint32_t tick;
		uint32_t game_object_id;
		uint32_t command_type;
		int32_t x;
		int32_t y;

		*packet
			>> client_id
			>> player_id
			>> tick
			>> game_object_id
			>> command_type
			>> x
			>> y
			;

		for (uint32_t i = 0; i <= game->open_slots; i++) {
			auto& world = worlds[i];
			if (i == player_id || i == 0) {
				world->commands[tick].push_back(
					std::make_unique<MoveCommand>(game_object_id, x, y)
				);

				if (tick < world->latest_tick) {
					world->rollback = true;
					if (world->rollback_tick > tick) {
						world->rollback_tick = tick;
					}
				}

				if (i == player_id) {
					world->ack_tick = tick;
				}
			}
			else {
				MoveCommand move_command();
				world->commands[tick + default_delay_tick].push_back(
					std::make_unique<MoveCommand>(game_object_id, x, y)
				);

				if (tick + default_delay_tick < world->latest_tick) {
					world->rollback = true;
					if (world->rollback_tick > tick + default_delay_tick) {
						world->rollback_tick = tick + default_delay_tick;
					}
				}
			}
		}

		RelayMovePacket(
			client_id, 
			tick + default_delay_tick, 
			MoveCommand(game_object_id, x, y)
		);

		return true;
	}

	default: {
		return false;
	}

	}
}

void MainScene::SendLoadPacket() {
	auto server_load_packet = std::make_shared<Packet>(PacketType::ServerLoad);

	uint32_t game_objects_count = worlds[0]->game_objects.size();
	*server_load_packet << game_objects_count;

	for (auto& game_object_container : worlds[0]->game_objects) {
		GameObject* game_object = game_object_container.second.get();

		uint32_t type = game_object->GetType();
		uint32_t id = game_object->GetId();

		float position_x, position_y;
		game_object->GetPosition(position_x, position_y);

		*server_load_packet
			<< type << id
			<< position_x << position_y
			;

		switch (type) {
		case ACTOR_TYPE_TANK: {
			Tank* tank = static_cast<Tank*>(game_object);
			uint32_t player_id = tank->GetPlayerId();
			*server_load_packet << player_id;
			break;
		}
		}

	}

	game->SendAll(server_load_packet);
}

void MainScene::SendStartGamePacket() {
	auto start_game_packet = std::make_shared<Packet>(PacketType::StartGame);
	game->SendAll(start_game_packet);
}

void MainScene::SendGameStatePacket(uint32_t client_id, pWorld world) {
	auto& records = world->records[world->latest_tick - default_delay_tick];

	auto game_state_packet = std::make_shared<Packet>(PacketType::ServerGameState);
	
	uint32_t ack_tick = world->latest_tick - default_delay_tick;
	*game_state_packet << ack_tick;

	uint32_t game_object_count = records.size();
	*game_state_packet << game_object_count;

	for (auto& record : records) {
		uint32_t type = record->game_object_type;
		uint32_t id = record->game_object_id;
		float position_x = record->position_x;
		float position_y = record->position_y;
		float velocity_x = record->velocity_x;
		float velocity_y = record->velocity_y;

		switch (type){
		case ACTOR_TYPE_TANK: {
			TankRecord* tank_record = static_cast<TankRecord*>(record.get());
			uint32_t player_id = tank_record->player_id;
			int32_t movement_x = tank_record->current_movement_x;
			int32_t movement_y = tank_record->current_movement_y;

			*game_state_packet
				<< type << id
				<< position_x << position_y
				<< velocity_x << velocity_y
				<< player_id
				<< movement_x << movement_y
				;

			break;
		}
		}
	}

	game->Send(client_id, game_state_packet);
}

void MainScene::SendReplyPingPacket(uint32_t client_id, uint32_t reply_ping_tick) {
	auto ping_reply_packet = std::make_shared<Packet>(PacketType::Ping);
	*ping_reply_packet << reply_ping_tick;
	game->Send(client_id, ping_reply_packet);
}

void MainScene::RelayMovePacket(uint32_t client_id, uint32_t tick, MoveCommand move_command) {
	auto relay_move_command_packet = std::make_shared<Packet>(PacketType::PlayerMove);
	*relay_move_command_packet
		<< tick
		<< move_command.game_object_id
		<< move_command.command_type
		<< move_command.x
		<< move_command.y
		;
	game->SendAllExcept(client_id, relay_move_command_packet);
}