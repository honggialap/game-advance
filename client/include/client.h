#pragma once
#ifndef __CLIENT__CLIENT_H__
#define __CLIENT__CLIENT_H__

#include "common.h"
#include "connection.h"

class Client {
protected:
	std::mutex			mutex;
	
	bool				is_initialized		= false;
	WSADATA				wsa_data;
	
	bool				is_connecting		= false;
	IPEndPoint			host_address;
	Connection			connection;
	WSAPOLLFD			master_fd;

	bool				is_accepted			= false;
	uint32_t			client_id			= 0;

public:
	void SetHostAddress(IPEndPoint value) { host_address = value; }
	IPEndPoint GetHostAddress() { return host_address; }

	void AssignClientId(uint32_t value) { client_id = value; }
	uint32_t GetClientId() { return client_id; }

	bool Initialize();
	bool Shutdown();

	bool Connect();
	bool Disconnect();

	bool ProcessNetworks();
	bool ProcessPackets();

	bool Send(std::shared_ptr<Packet> packet);
	virtual bool ProcessPacket(std::shared_ptr<Packet> packet);

	virtual void OnConnect() = 0;
	virtual void OnDisconnect() = 0;
	virtual void OnConnectFail() = 0;
};

#endif // !__CLIENT__CLIENT_H__
