#pragma once
#ifndef __ENGINE_CLIENT_H__
#define __ENGINE_CLIENT_H__

#include "common.h"
#include "connection.h"

namespace Engine {

	class Client {
	protected:
		bool is_connecting = false;
		WSADATA wsa_data;
		Connection connection;		
		WSAPOLLFD master_fd;
		WSAPOLLFD temp_fd;

	public:

		bool IsConnecting() { return is_connecting; }

		bool Connect(IPEndPoint ip_endpoint);
		void CleanUp();

		virtual void OnConnect();
		virtual void OnDisconnect();
		virtual void OnConnectFail();

		bool ProcessNetworks();

		void CloseConnection();
		virtual bool ProcessPacket(std::shared_ptr<Packet> packet);
	};

}

#endif // !__ENGINE_CLIENT_H__
