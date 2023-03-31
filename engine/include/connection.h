#pragma once
#ifndef __ENGINE_CONNECTION_H__
#define __ENGINE_CONNECTION_H__

#include "common.h"
#include "socket.h"
#include "packet_manager.h"

class Connection {
private:
	IPEndPoint ip_endpoint;

public:
	Socket socket;
	char buffer[MAX_PACKET_SIZE];
	PacketManager imcomming_packets;
	PacketManager outgoing_packets;

	Connection() : socket(Socket()) {}
	Connection(Socket socket, IPEndPoint ip_endpoint);
	void Close();
};

#endif // !__ENGINE_CONNECTION_H__
