#include "host_connection.h"

namespace Engine {

	bool HostConnection::Connect(const char* address, const char* port) {
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed with error: %d\n", iResult);
			return false;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		iResult = getaddrinfo(address, port, &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			return false;
		}

		for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

			connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
			if (connectSocket == INVALID_SOCKET) {
				printf("socket failed with error: %ld\n", WSAGetLastError());
				WSACleanup();
				return false;
			}

			iResult = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR) {
				closesocket(connectSocket);
				connectSocket = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(result);

		if (connectSocket == INVALID_SOCKET) {
			printf("Unable to connect to server!\n");
			WSACleanup();
			return false;
		}

		printf("Connected to server!\n");
		char id_message[4];
		iResult = recv(connectSocket, id_message, sizeof(&id_message), 0);
		if (iResult > 0) {
			id = std::stoul(id_message, nullptr, 0);
			printf("Bytes received: %d\n", iResult);
			printf("ID accquired: %d\n", id);
			return true;
		}
		else if (iResult == 0) {
			printf("Connection closed\n");
			closesocket(connectSocket);
			WSACleanup();
			return false;
		}
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(connectSocket);
			WSACleanup();
			return false;
		}
	}

	void HostConnection::Disconnect() {
		int iResult = shutdown(connectSocket, SD_BOTH);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed with error: %d\n", WSAGetLastError());
		}

		closesocket(connectSocket);
		WSACleanup();

		printf("Disconnected from server!\n");
	}

	bool HostConnection::Send(const char* message) {
		int iResult = send(connectSocket, message, (int)strlen(message), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(connectSocket);
			WSACleanup();
			return false;
		}

		printf("Bytes Sent: %ld\n", iResult);
		return true;
	}

	bool HostConnection::Receive(char* buffer, int buffer_length) {
		int iResult = recv(connectSocket, buffer, buffer_length, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);
			return true;
		}
		else if (iResult == 0) {
			printf("Connection closed\n");
			return false;
		}
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			return false;
		}
	}
}