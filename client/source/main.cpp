#include "connection.h"

int main() {
	//Client::GameClient game_client;
	//game_client.Run("data/game_data.json");

	Engine::Connection host_connection;
	if (host_connection.Initialize()) {
		Engine::Socket socket;
		if (socket.Create()) {
			if (socket.Connect(Engine::IPEndPoint("localhost", 27015))) {
				
				Engine::Packet string_packet(Engine::ChatMessage);
				string_packet << std::string("this is a chat message packet!");

				Engine::Packet int_array_packet(Engine::IntArray);
				uint32_t array_size = 3;
				uint32_t int_array[3] = { 1, 2, 3 };
				int_array_packet << array_size;
				for (auto element : int_array) {
					int_array_packet << element;
				}

				while (true) {
					if (!socket.Send(string_packet)) {
						break;
					}

					if (!socket.Send(int_array_packet)) {
						break;
					}

					Sleep((DWORD)1000);
				}
			}
			socket.Close();
		}
		host_connection.Shutdown();
	}

	system("pause");
	return 0;
}