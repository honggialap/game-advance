#pragma once
#ifndef __CLIENT_CLIENT_H__
#define __CLIENT_CLIENT_H__

#include "common.h"
#include "connection.h"

class Client {
protected:
	bool is_initialized = false;
	WSADATA wsa_data;
	IPEndPoint host_address;

	bool is_connecting = false;
	std::pair<Connection, WSAPOLLFD> host_connection;

	bool is_approved = false;
	uint32_t id;

public:
	bool Initialize(IPEndPoint ip_endpoint);
	bool Shutdown();

	bool Connect();
	bool Disconnect();

	bool ProcessNetworks();
	bool Send(std::shared_ptr<Packet> packet);

	void AssignId(uint32_t id) { this->id = id; is_approved = true; }
	bool IsApproved() { return is_approved; }
	uint32_t GetId() { return id; }

	virtual void OnConnect() = 0;
	virtual void OnDisconnect() = 0;
	virtual void OnConnectFail() = 0;
	virtual bool ProcessPacket(std::shared_ptr<Packet> packet) = 0;
};

#endif // !__CLIENT_CLIENT_H__
