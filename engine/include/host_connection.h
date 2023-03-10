#pragma once
#ifndef __ENGINE_HOSTCONNECTION_H__
#define __ENGINE_HOSTCONNECTION_H__

#include "common.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

namespace Engine {

	class HostConnection {
	protected:
		WSADATA wsaData;

		uint32_t id;
		SOCKET connectSocket = INVALID_SOCKET;

		struct addrinfo
			* result = NULL,
			* ptr = NULL,
			hints;

	public:
		bool Connect(const char* address, const char* port);
		void Disconnect();

		bool Send(const char* message);
		bool Receive(char* buffer, int buffer_length);
	};
	typedef HostConnection* pHostConnection;

}

#endif // !__ENGINE_HOSTCONNECTION_H__
