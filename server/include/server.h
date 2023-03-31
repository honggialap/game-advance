#pragma once
#ifndef __SERVER_SERVER_H__
#define __SERVER_SERVER_H__

#include "common.h"
#include "connection.h"

class Server {
protected:
	bool is_initialized = false;
	WSADATA wsa_data;

	bool is_listening = false;
	std::pair<Socket, WSAPOLLFD> listener;

	bool is_processing = false;
	uint32_t client_id = 1000;
	uint32_t max_connection_count = 0;
	std::map<uint32_t, std::tuple<Connection, WSAPOLLFD, bool>> connections;

public:
	bool Initialize();
	bool Shutdown();

	bool StartListening(IPEndPoint ip_endpoint, uint32_t connection_count);
	bool StopListening();
	bool Listening();

	bool Accept(uint32_t id, Connection connection, WSAPOLLFD connection_master_fd);
	bool Disconnect(uint32_t id);
	bool DisconnectAll();
	bool CleanUpDisconnected();

	bool ProcessIncomming();
	bool ProcessNetworks();
	
	bool Send(uint32_t id, std::shared_ptr<Packet> packet);

	virtual void OnConnect(uint32_t connection_id) = 0;
	virtual void OnDisconnect(uint32_t connection_id) = 0;
	virtual bool ProcessPacket(std::shared_ptr<Packet> packet) = 0;
};

#endif // !__SERVER_SERVER_H__
