#pragma once
#ifndef __ENGINE_REMOTECONNECTION_H__
#define __ENGINE_REMOTECONNECTION_H__

#include "common.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")

namespace Engine {

	class RemoteConnection {
	protected:
		WSADATA wsaData;

		SOCKET listenSocket = INVALID_SOCKET;

		std::map<uint32_t, SOCKET> connectSockets;
		uint32_t id = 1000;

		struct addrinfo
			* result = NULL,
			hints;

	public:
		bool Listen(const char* port);
		bool Accept();
		
		void Disconnect(uint32_t id);
		void Shutdown();

		bool Send(uint32_t id, const char* message);
		bool Receive(char* buffer, int buffer_length);
	};
	typedef RemoteConnection* pRemoteConnection;

}

#endif // !__ENGINE_REMOTECONNECTION_H__
