#include "server.h"

int main() {
	const char* send_buffer = "this is a test message from server to client.";

	const int receive_buffer_len = 512;
	char receive_buffer[receive_buffer_len];

	Server::Networks connection;
	if (connection.Listen("27015")) {
		while (connection.Accept()) {
			for (auto& client : connection.GetClients()) {
			}
		}
		connection.Shutdown();
	}

	system("pause");

	return 0;
}