#pragma once
#ifndef __ENGINE_CLIENT_H__
#define __ENGINE_CLIENT_H__

#include "common.h"
#include "connection.h"

namespace Engine {

	class Client {
	protected:
		WSADATA wsa_data;
		bool is_initialized = false;

		Connection connection;
		bool is_connecting = false;
				
		WSAPOLLFD master_fd;
		WSAPOLLFD temp_fd;

	public:
		bool Initialize();
		bool Shutdown();
		bool IsInitialized() { return is_initialized; }

		bool Connect(IPEndPoint ip_endpoint);
		bool Disconnect();
		bool IsConnecting() { return is_connecting; }

		bool ProcessNetworks();

		virtual void OnConnect() = 0;
		virtual void OnDisconnect() = 0;
		virtual void OnConnectFail() = 0;
		virtual bool ProcessPacket(std::shared_ptr<Packet> packet) = 0;
	};

}

#endif // !__ENGINE_CLIENT_H__
