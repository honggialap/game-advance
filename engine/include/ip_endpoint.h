#pragma once
#ifndef __ENGINE_IPENDPOINT_H__
#define __ENGINE_IPENDPOINT_H__

#include "common.h"

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
		IPEndPoint() {};
		IPEndPoint(const char* ip, unsigned int port);
		IPEndPoint(sockaddr* addr);

		sockaddr_in GetSockaddrIPv4();
		sockaddr_in6 GetSockaddrIPv6();
	};

}

#endif // !__ENGINE_IPENDPOINT_H__
