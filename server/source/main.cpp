#include "connection.h"

bool ProcessPacket(Engine::Packet& packet) {
	switch (packet.GetPacketType())
	{
	case Engine::ChatMessage: {
		std::string message;
		packet >> message;
		std::cout << message << std::endl;
		break;
	}

	case Engine::IntArray: {
		uint32_t array_size = 0;
		packet >> array_size;
		std::cout << "Array size: " << array_size << std::endl;
		for (uint32_t it = 0; it < array_size; it++) {
			uint32_t element = 0;
			packet >> element;
			std::cout << "Element[" << it << "] - " << element << std::endl;
		}
		break;
	}

	case Engine::Invalid:
	default:
		return false;
	}
	return true;
}

int main() {
	//Server::GameServer game_server;
	//game_server.Run("data/game_data.json");

	Engine::Connection remote_connection;
	if (remote_connection.Initialize()) {
		Engine::Socket socket(Engine::IPv6);
		if (socket.Create()) {
			if (socket.Listen(Engine::IPEndPoint("::", 27015))) {
				Engine::Socket new_client;
				if (socket.Accept(new_client)) {

					Engine::Packet packet;
					while (true) {
						if (!new_client.Recv(packet)) {
							break;
						}
						if (!ProcessPacket(packet)) {
							break;
						}
					}

					new_client.Close();
				}
			}
			socket.Close();
		}
		remote_connection.Shutdown();
	}

	system("pause");
	return 0;
}