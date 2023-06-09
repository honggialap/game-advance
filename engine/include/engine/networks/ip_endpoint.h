#pragma once
#ifndef __ENGINE__NETWORKS__IP_END_POINT_H__
#define __ENGINE__NETWORKS__IP_END_POINT_H__

#include "engine/common.h"

namespace NSEngine {
	namespace NSNetworks {

		enum EIPVersion {
			Unknown,
			IPv4,
			IPv6
		};

		class CIPEndPoint {
		private:
			EIPVersion ip_version = EIPVersion::Unknown;
			std::string host_name;
			std::string ip_string;
			std::vector<uint8_t> ip_bytes;
			unsigned short port = 0;

		public:
			EIPVersion GetIPVersion();
			std::string GetHostName();
			std::string GetIPString();
			std::vector<uint8_t> GetIPBytes();
			unsigned short GetPort();

		public:
			CIPEndPoint();
			CIPEndPoint(const char* ip, unsigned int port);
			CIPEndPoint(sockaddr* addr);

			sockaddr_in GetSockaddrIPv4();
			sockaddr_in6 GetSockaddrIPv6();
		};

	}
}

#endif // !__ENGINE__NETWORKS__IP_END_POINT_H__
