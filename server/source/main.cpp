#include "remote_connection.h"

int main() {

	Engine::RemoteConnection connection;
	if (connection.Listen("27015")) {
		while (connection.Accept()) {
		}
		connection.Shutdown();
	}

	system("pause");

	return 0;
}