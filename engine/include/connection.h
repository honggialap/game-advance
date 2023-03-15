#pragma once
#ifndef __ENGINE_CONNECTION_H__
#define __ENGINE_CONNECTION_H__

#include "common.h"
#include "packet.h"

namespace Engine {
	
	enum IPVersion {
		Unknown,
		IPv4,
		IPv6
	};

	class IPEndPoint {
	private:
		IPVersion ip_version = IPVersion::Unknown;
		std::string host_name;
		std::string ip_string;
		std::vector<uint8_t> ip_bytes;
		unsigned short port = 0;

	public:
		IPVersion GetIPVersion() { return ip_version; }
		std::string GetHostName() { return host_name; }
		std::string GetIPString() { return ip_string; }
		std::vector<uint8_t> GetIPBytes() { return ip_bytes; }
		unsigned short GetPort() { return port; }

	public:
		IPEndPoint(const char* ip, unsigned int port);
		IPEndPoint(sockaddr* addr);

		sockaddr_in GetSockaddrIPv4();
		sockaddr_in6 GetSockaddrIPv6();
	};

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
		bool Create();
		bool Close();

		bool Bind(IPEndPoint ip_endpoint);
		bool Listen(IPEndPoint ip_endpoint, int backlog = 5);
		bool Accept(Socket& out_socket);
		bool Connect(IPEndPoint ip_endpoint);

		bool Send(const void* data, int bytes, int& sent_bytes);
		bool Recv(void* destination, int bytes, int& received_bytes);

		bool SendAll(const void* data, int bytes);
		bool RecvAll(void* destination, int bytes);

		bool Send(Packet& packet);
		bool Recv(Packet& packet);
	};

	class Connection {
	protected:
		WSADATA wsa_data;

	public:
		bool Initialize();
		void Shutdown();
	};
	typedef Connection* pConnection;
}

#endif // !__ENGINE_CONNECTION_H__
