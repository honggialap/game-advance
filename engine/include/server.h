#pragma once
#ifndef __ENGINE_SERVER_H__
#define __ENGINE_SERVER_H__

#include "common.h"
#include "connection.h"

namespace Engine {

	class Server {
	protected:
		bool is_initialized = false;
		WSADATA wsa_data;

		bool is_listening = false;
		std::pair<Socket, WSAPOLLFD> listener;

		uint32_t client_id = 1000;
		std::map<uint32_t, std::tuple<Connection, WSAPOLLFD, bool>> connections;

	public:
		bool Initialize();
		bool Shutdown();
		bool IsInitialized() { return is_initialized; }

		bool Listen(IPEndPoint ip_endpoint);
		bool Disconnect(uint32_t connection_id);
		bool IsListening() { return is_listening; }

		bool ProcessListening();
		bool ProcessConnection();

		virtual void OnConnect(uint32_t connection_id) = 0;
		virtual void OnDisconnect(uint32_t connection_id) = 0;
		virtual bool ProcessPacket(std::shared_ptr<Packet> packet) = 0;

	};

}

#endif // !__ENGINE_SERVER_H__
