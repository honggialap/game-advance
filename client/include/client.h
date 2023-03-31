#pragma once
#ifndef __CLIENT_CLIENT_H__
#define __CLIENT_CLIENT_H__

#include "common.h"
#include "connection.h"

class Client {
protected:
	bool is_initialized = false;
	WSADATA wsa_data;

	bool is_connecting = false;
	uint32_t id;
	std::pair<Connection, WSAPOLLFD> host_connection;

public:
	bool Initialize();
	bool Shutdown();

	bool Connect(IPEndPoint ip_endpoint);
	bool Disconnect();

	bool ProcessIncomming();
	bool ProcessNetworks();

	bool Send(std::shared_ptr<Packet> packet);

	virtual void OnConnect() = 0;
	virtual void OnDisconnect() = 0;
	virtual void OnConnectFail() = 0;
	virtual bool ProcessPacket(std::shared_ptr<Packet> packet) = 0;
};

#endif // !__CLIENT_CLIENT_H__
