#include "remote_connection.h"

namespace Engine {

	bool RemoteConnection::Listen(const char* port) {
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed with error: %d\n", iResult);
			return false;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		iResult = getaddrinfo(NULL, port, &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			return false;
		}

		listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (listenSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			return false;
		}

		iResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			printf("bind failed with error: %d\n", WSAGetLastError());
			freeaddrinfo(result);
			closesocket(listenSocket);
			WSACleanup();
			return false;
		}

		freeaddrinfo(result);

		iResult = listen(listenSocket, SOMAXCONN);
		if (iResult == SOCKET_ERROR) {
			printf("listen failed with error: %d\n", WSAGetLastError());
			closesocket(listenSocket);
			WSACleanup();
			return false;
		}

		return true;
	}

	bool RemoteConnection::Accept() {
		SOCKET newSocket = accept(listenSocket, NULL, NULL);
		if (newSocket != INVALID_SOCKET) {
			connectSockets[id] = newSocket;

			std::string id_message = std::to_string(id);
			int iResult = send(connectSockets[id], id_message.c_str(), (int)strlen(id_message.c_str()), 0);
			if (iResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				Disconnect(id);
				WSACleanup();
				return false;
			}

			printf("Bytes sent: %d\n", iResult);
			printf("ID sent: %d\n", id);
			id++;
			return true;
		}
		else if (newSocket == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(listenSocket);
			WSACleanup();
			return false;
		}

		return false;
	}

	void RemoteConnection::Disconnect(uint32_t id) {
		int iResult = shutdown(connectSockets[id], SD_BOTH);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed with error: %d\n", WSAGetLastError());
		}

		closesocket(connectSockets[id]);
		connectSockets.erase(id);
	}

	void RemoteConnection::Shutdown() {
		for (auto& connection : connectSockets) {
			int iResult = shutdown(connection.second, SD_BOTH);
			if (iResult == SOCKET_ERROR) {
				printf("shutdown failed with error: %d\n", WSAGetLastError());
			}

			closesocket(connection.second);
		}
		connectSockets.clear();

		closesocket(listenSocket);
		WSACleanup();
	}

	bool RemoteConnection::Send(uint32_t id, const char* message) {
		int iResult = send(connectSockets[id], message, (int)strlen(message), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			Disconnect(id);
			WSACleanup();
			return false;
		}

		printf("Bytes sent: %d\n", iResult);
		return true;
	}

	bool RemoteConnection::Receive(char* buffer, int buffer_length) {
		int iResult = recv(connectSockets[id], buffer, buffer_length, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);
			return true;
		}
		else if (iResult == 0) {
			printf("Connection closing...\n");
			return false;
		}
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			Disconnect(id);
			WSACleanup();
			return false;
		}
	}

}