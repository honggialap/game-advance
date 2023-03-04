#include "client.h"

int main() {
	const char* send_buffer = "this is a test message from client to server.";

	const int receive_buffer_len = 512;
	char receive_buffer[receive_buffer_len];

	Client::Networks connection;
	if (connection.Connect("localhost", "27015")) {
		Sleep(1000);
		connection.Disconnect();
	}

	system("pause");

	return 0;
}