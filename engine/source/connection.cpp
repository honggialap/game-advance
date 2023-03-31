#include "connection.h"

Connection::Connection(Socket socket, IPEndPoint ip_endpoint)
	: socket(socket), ip_endpoint(ip_endpoint) {
}

void Connection::Close() {
	socket.Close();
}
