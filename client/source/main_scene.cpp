#include "main_scene.h"
#include "game.h"

#include "tank.h"
#include "bullet.h"
#include "wall.h"

void MainScene::Load(std::string data_path) {
	std::ifstream data_file(data_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	camera.reset(sf::FloatRect(0, 0, 800, 600));
	camera.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	font.loadFromFile("data/resources/fonts/arial.ttf");
	text.setFont(font);

	world = new World();
}

void MainScene::Unload() {
	if (world) {
		world->game_objects.clear();
		delete world;
		world = nullptr;
	}
}

void MainScene::Update(float elapsed) {
	switch (state) {
	case MainScene::Loading:
		if (!ready_sent) {
			SendReadyPacket();
			ready_sent = true;
		}
		break;

	case MainScene::Run: {
		for (auto& game_object_container : world->game_objects) {
			game_object_container.second->HandleInput(current_tick);
		}

		if (world->commands.find(current_tick) != world->commands.end()) {
			auto& current_tick_commands = world->commands.at(current_tick);
			for (auto& command : current_tick_commands) {
				world->game_objects[
					command->game_object_id
				]->ExecuteCommand(command.get());
			}
		}

		for (auto& game_object_container : world->game_objects) {
			game_object_container.second->Update(elapsed);
		}
		world->physics_world->Step(elapsed, 8, 3);

		if (!world->commands.empty() && current_tick > 64) {
			while (
				!world->commands.empty()
				&& world->commands.begin()->first < current_tick - 64
				) {
				auto erasing_tick = world->commands.begin()->first;
				world->commands.erase(erasing_tick);
			}
		}

		if (!ping_sent) {
			SendPingPacket();
			ping_sent = true;
		}

		current_tick += 1;
		break;
	}
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
		for (auto& game_object_container : world->game_objects) {
			game_object_container.second->Render(window);
		}
		break;
	}
	}

}

sf::View& MainScene::GetCamera() {
	return camera;
}

void MainScene::OnConnect() {

}

void MainScene::OnDisconnect() {

}

void MainScene::OnConnectFail() {

}

bool MainScene::ProcessPacket(std::shared_ptr<Packet> packet) {
	switch (packet->GetPacketType()) {

	case PacketType::ServerLoad: {
		uint32_t game_object_count = 0;
		*packet >> game_object_count;

		for (uint32_t i = 0; i < game_object_count; i++) {
			uint32_t type = 0;
			uint32_t id = 0;
			float position_x = 0.0f;
			float position_y = 0.0f;

			*packet
				>> type >> id
				>> position_x >> position_y;

			switch (type) {
			case ACTOR_TYPE_TANK: {
				uint32_t player_id = 0;
				*packet >> player_id;

				auto tank = static_cast<Tank*>(world->CreateGameObject(game, type, position_x, position_y));
				tank->SetPlayerId(player_id);
				if (tank->GetPlayerId() == game->player_id) {
					tank->SetPlayerControl(true);
				}
				break;
			}
			}
		}

		SendLoadPacket();

		return true;
	}

	case PacketType::StartGame: {
		state = State::Run;
		return true;
	}

	case PacketType::Ping: {
		uint32_t reply_ping_tick;
		*packet >> reply_ping_tick;
		ping_tick = (current_tick - reply_ping_tick) / 2;
		ping_sent = false;
		return true;
	}

	case PacketType::ServerGameState: {
		return true;
	}

	case PacketType::PlayerMove: {
		uint32_t tick;
		uint32_t game_object_id;
		uint32_t command_type;
		int32_t x;
		int32_t y;
		
		*packet
			>> tick
			>> game_object_id
			>> command_type
			>> x
			>> y
			;

		MoveCommand move_command(game_object_id, x, y);
		world->commands[tick].push_back(
			std::make_unique<MoveCommand>(move_command)
		);
		return true;
	}

	default: {
		return false;
	}

	}
}

void MainScene::SendReadyPacket() {
	auto ready_packet = std::make_shared<Packet>(PacketType::ClientReady);
	game->Send(ready_packet);
}

void MainScene::SendLoadPacket() {
	auto client_load_packet = std::make_shared<Packet>(PacketType::ClientLoad);
	game->Send(client_load_packet);
}

void MainScene::SendPingPacket() {
	auto ping_packet = std::make_shared<Packet>(PacketType::Ping);
	*ping_packet
		<< game->GetClientId()
		<< game->player_id
		<< current_tick
		<< ping_tick
		;
	game->Send(ping_packet);
	ping_sent = true;
}