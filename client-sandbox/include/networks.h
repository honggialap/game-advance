#pragma once
#ifndef __CLIENT_NETWORKS_H__
#define __CLIENT_NETWORKS_H__
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include "common.h"

namespace Client {
	class Networks {
	protected:
		WSADATA wsaData;

		uint32_t id;
		SOCKET connectSocket = INVALID_SOCKET;

		struct addrinfo
			* result = NULL,
			* ptr = NULL,
			hints;

	public:
		bool Connect(const char* address, const char* port) {
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
			ReceiveId();
			return true;
		}

		void Disconnect() {
			int iResult = shutdown(connectSocket, SD_BOTH);
			if (iResult == SOCKET_ERROR) {
				printf("shutdown failed with error: %d\n", WSAGetLastError());
			}

			closesocket(connectSocket);
			WSACleanup();

			printf("Disconnected from server!\n");
		}

		bool Send(const char* message) {
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

		bool Receive(char* buffer, int buffer_length) {
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

		bool ReceiveId() {
			char id_message[4];
			int iResult = recv(connectSocket, id_message, sizeof(&id_message), 0);
			if (iResult > 0) {
				id = std::stoul(id_message, nullptr, 0);
				printf("Bytes received: %d\n", iResult);
				printf("ID accquired: %d\n", id);
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
	};
}

#endif // !__CLIENT_NETWORKS_H__
