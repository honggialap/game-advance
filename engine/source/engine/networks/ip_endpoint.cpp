#include "engine/networks/ip_endpoint.h"

namespace NSEngine {
	namespace NSNetworks {

		EIPVersion CIPEndPoint::GetIPVersion() {
			return ip_version;
		}

		std::string CIPEndPoint::GetHostName() {
			return host_name;
		}

		std::string CIPEndPoint::GetIPString() {
			return ip_string;
		}

		std::vector<uint8_t> CIPEndPoint::GetIPBytes() {
			return ip_bytes;
		}

		unsigned short CIPEndPoint::GetPort() {
			return port;
		}

		CIPEndPoint::CIPEndPoint() {
		}

		CIPEndPoint::CIPEndPoint(const char* ip, unsigned int port)
			: port(port) {
			int result = 0;

			// IPv4
			in_addr addr;
			result = inet_pton(AF_INET, ip, &addr);
			if (result == 1) {
				if (addr.S_un.S_addr != INADDR_NONE) {
					ip_string = ip;
					host_name = ip;

					ip_bytes.resize(sizeof(ULONG));
					memcpy(&ip_bytes[0], &addr.S_un.S_addr, sizeof(ULONG));

					ip_version = EIPVersion::IPv4;
					return;
				}
			}

			addrinfo hints = {};
			hints.ai_family = AF_INET;
			addrinfo* host_info = nullptr;
			result = getaddrinfo(ip, NULL, &hints, &host_info);
			if (result == 0) {
				sockaddr_in* host_addr = reinterpret_cast<sockaddr_in*>(host_info->ai_addr);

				ip_string.resize(16);
				inet_ntop(AF_INET, &host_addr->sin_addr, &ip_string[0], 16);

				host_name = ip;

				ULONG ip_long = host_addr->sin_addr.S_un.S_addr;
				ip_bytes.resize(sizeof(ULONG));
				memcpy(&ip_bytes[0], &ip_long, sizeof(ULONG));

				ip_version = EIPVersion::IPv4;

				freeaddrinfo(host_info);
				return;
			}

			// IPv6
			in6_addr addr6;
			result = inet_pton(AF_INET6, ip, &addr6);
			if (result == 1) {
				ip_string = ip;
				host_name = ip;

				ip_bytes.resize(16);
				memcpy(&ip_bytes[0], &addr6.u, 16);

				ip_version = EIPVersion::IPv6;
				return;
			}

			addrinfo hintsv6 = {};
			hints.ai_family = AF_INET6;
			addrinfo* host_infov6 = nullptr;
			result = getaddrinfo(ip, NULL, &hintsv6, &host_infov6);
			if (result == 0) {
				sockaddr_in6* host_addr = reinterpret_cast<sockaddr_in6*>(host_infov6->ai_addr);

				ip_string.resize(46);
				inet_ntop(AF_INET6, &host_addr->sin6_addr, &ip_string[0], 46);

				host_name = ip;

				ip_bytes.resize(16);
				memcpy(&ip_bytes[0], &host_addr->sin6_addr, 16);

				ip_version = EIPVersion::IPv6;

				freeaddrinfo(host_info);
				return;
			}
		}

		CIPEndPoint::CIPEndPoint(sockaddr* addr) {
			if (addr->sa_family == AF_INET) {
				sockaddr_in* addrv4 = reinterpret_cast<sockaddr_in*>(addr);
				ip_version = EIPVersion::IPv4;
				port = ntohs(addrv4->sin_port);
				ip_bytes.resize(sizeof(ULONG));
				memcpy(&ip_bytes[0], &addrv4->sin_addr, sizeof(ULONG));
				ip_string.resize(16);
				inet_ntop(AF_INET, &addrv4->sin_addr, &ip_string[0], 16);
				host_name = ip_string;
			}
			else if (addr->sa_family == AF_INET6) {
				sockaddr_in6* addrv6 = reinterpret_cast<sockaddr_in6*>(addr);
				ip_version = EIPVersion::IPv6;
				port = ntohs(addrv6->sin6_port);
				ip_bytes.resize(16);
				memcpy(&ip_bytes[0], &addrv6->sin6_addr, 16);
				ip_string.resize(46);
				inet_ntop(AF_INET6, &addrv6->sin6_addr, &ip_string[0], 46);
				host_name = ip_string;
			}
		}

		sockaddr_in CIPEndPoint::GetSockaddrIPv4() {
			sockaddr_in addr = {};
			addr.sin_family = AF_INET;
			memcpy(&addr.sin_addr, &ip_bytes[0], sizeof(ULONG));
			addr.sin_port = htons(port);
			return addr;
		}

		sockaddr_in6 CIPEndPoint::GetSockaddrIPv6() {
			sockaddr_in6 addr = {};
			addr.sin6_family = AF_INET6;
			memcpy(&addr.sin6_addr, &ip_bytes[0], 16);
			addr.sin6_port = htons(port);
			return addr;
		}

	}
}