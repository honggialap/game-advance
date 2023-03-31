#pragma once
#ifndef __ENGINE_SOCKET_H__
#define __ENGINE_SOCKET_H__

#include "common.h"
#include "ip_endpoint.h"
#include "packet.h"

typedef SOCKET SocketHandle;

enum SocketOption {
	TCP_NoDelay,
	IPv6_Only
};

class Socket {
private:
	IPVersion ip_version = IPVersion::IPv4;
	SocketHandle socket_handle = INVALID_SOCKET;

public:
	IPVersion GetIPVersion() { return ip_version; }
	SocketHandle GetSocketHandle() { return socket_handle; }

public:
	Socket(
		IPVersion ip_version = IPVersion::IPv4,
		SocketHandle socket_handle = INVALID_SOCKET
	);

private:
	bool SetSocketOption(SocketOption socket_option, BOOL value);

public:
	bool SetSocketBlocking(bool is_blocking);

	bool Create();
	bool Close();

	bool Bind(IPEndPoint ip_endpoint);
	bool Listen(IPEndPoint ip_endpoint, int backlog = 5);
	bool Accept(Socket& out_socket, IPEndPoint* ip_endpoint = nullptr);
	bool Connect(IPEndPoint ip_endpoint);

	bool Send(const void* data, int bytes, int& sent_bytes);
	bool Recv(void* destination, int bytes, int& received_bytes);

	bool SendAll(const void* data, int bytes);
	bool RecvAll(void* destination, int bytes);

	bool Send(Packet& packet);
	bool Recv(Packet& packet);
};

#endif // !__ENGINE_SOCKET_H__
