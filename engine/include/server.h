#pragma once
#ifndef __ENGINE_SERVER_H__
#define __ENGINE_SERVER_H__

#include "common.h"
#include "connection.h"

namespace Engine {

	class Server {
	protected:
		bool is_running;
		WSADATA wsa_data;
		Socket listening_socket;
		std::vector<Connection> connections;
		std::vector<WSAPOLLFD> master_fd;
		std::vector<WSAPOLLFD> temp_fd;
		
	public:
		bool IsRunning() { return is_running; }

		bool Listen(IPEndPoint ip_endpoint);
		void CleanUp();

		virtual void OnConnect(Connection& connection);
		virtual void OnDisconnect(Connection& connection);
		
		void ProcessNetworks();

		void CloseConnection(int connection_index);
		virtual bool ProcessPacket(std::shared_ptr<Packet> packet);
		
	};

}

#endif // !__ENGINE_SERVER_H__
