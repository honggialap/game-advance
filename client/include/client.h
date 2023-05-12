#pragma once
#ifndef __CLIENT_CLIENT_H__
#define __CLIENT_CLIENT_H__

#include "common.h"
#include "connection.h"

class Client {
protected:
	std::mutex mutex;
	
	bool is_initialized = false;
	WSADATA wsa_data;
	IPEndPoint host_address;

	bool is_connecting = false;
	std::pair<Connection, WSAPOLLFD> host_connection;
	uint32_t client_id;

public:
	bool Initialize(IPEndPoint ip_endpoint);
	bool Shutdown();

	bool Connect();
	bool Disconnect();

	bool ProcessNetworks();
	bool ProcessPackets();

	bool Send(std::shared_ptr<Packet> packet);

	void AssignClientId(uint32_t value) { client_id = value; }
	uint32_t GetClientId() { return client_id; }

	virtual void OnConnect() = 0;
	virtual void OnDisconnect() = 0;
	virtual void OnConnectFail() = 0;
	virtual bool ProcessPacket(std::shared_ptr<Packet> packet) = 0;
};

#endif // !__CLIENT_CLIENT_H__
