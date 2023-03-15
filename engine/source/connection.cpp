#include "connection.h"

namespace Engine {

#pragma region CONNECTION

	bool Engine::Connection::Initialize() {
		int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
		if (result != 0) {
			return false;
		}

		if (LOBYTE(wsa_data.wVersion) != 2 || HIBYTE(wsa_data.wVersion) != 2) {
			return false;
		}

		return true;
	}

	void Engine::Connection::Shutdown() {
		WSACleanup();
	}

#pragma endregion

#pragma region IP_ENDPOINT

	IPEndPoint::IPEndPoint(const char* ip, unsigned int port)
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

				ip_version = IPVersion::IPv4;
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

			ip_version = IPVersion::IPv4;

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

			ip_version = IPVersion::IPv6;
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

			ip_version = IPVersion::IPv6;

			freeaddrinfo(host_info);
			return;
		}
	}

	IPEndPoint::IPEndPoint(sockaddr* addr) {
		if (addr->sa_family == AF_INET) {
			sockaddr_in* addrv4 = reinterpret_cast<sockaddr_in*>(addr);
			ip_version = IPVersion::IPv4;
			port = ntohs(addrv4->sin_port);
			ip_bytes.resize(sizeof(ULONG));
			memcpy(&ip_bytes[0], &addrv4->sin_addr, sizeof(ULONG));
			ip_string.resize(16);
			inet_ntop(AF_INET, &addrv4->sin_addr, &ip_string[0], 16);
			host_name = ip_string;
		}
		else if (addr->sa_family == AF_INET6) {
			sockaddr_in6* addrv6 = reinterpret_cast<sockaddr_in6*>(addr);
			ip_version = IPVersion::IPv6;
			port = ntohs(addrv6->sin6_port);
			ip_bytes.resize(16);
			memcpy(&ip_bytes[0], &addrv6->sin6_addr, 16);
			ip_string.resize(46);
			inet_ntop(AF_INET6, &addrv6->sin6_addr, &ip_string[0], 46);
			host_name = ip_string;
		}
	}

	sockaddr_in IPEndPoint::GetSockaddrIPv4() {
		sockaddr_in addr = {};
		addr.sin_family = AF_INET;
		memcpy(&addr.sin_addr, &ip_bytes[0], sizeof(ULONG));
		addr.sin_port = htons(port);
		return addr;
	}

	sockaddr_in6 IPEndPoint::GetSockaddrIPv6() {
		sockaddr_in6 addr = {};
		addr.sin6_family = AF_INET6;
		memcpy(&addr.sin6_addr, &ip_bytes[0], 16);
		addr.sin6_port = htons(port);
		return addr;
	}

#pragma endregion

#pragma region SOCKET

	Socket::Socket(IPVersion ip_version, SocketHandle socket_handle)
		: ip_version(ip_version), socket_handle(socket_handle) {
	}

	bool Socket::SetSocketOption(SocketOption socket_option, BOOL value) {
		int result = 0;
		switch (socket_option)
		{
		case Engine::TCP_NoDelay:
			result = setsockopt(
				socket_handle,
				IPPROTO_TCP,
				TCP_NODELAY,
				(const char*)&value
				, sizeof(value)
			);
			break;

		case Engine::IPv6_Only:
			result = setsockopt(
				socket_handle,
				IPPROTO_IPV6,
				IPV6_V6ONLY,
				(const char*)&value
				, sizeof(value)
			);
			break;

		default:
			return false;
			break;
		}

		if (result != 0) {
			int error = WSAGetLastError();
			return false;
		}

		return true;
	}

	bool Socket::Create() {
		if (socket_handle != INVALID_SOCKET) {
			return false;
		}

		socket_handle = socket((ip_version == IPVersion::IPv4) ? AF_INET : AF_INET6, SOCK_STREAM, IPPROTO_TCP);
		if (socket_handle == INVALID_SOCKET) {
			int error = WSAGetLastError();
			return false;
		}

		if (!SetSocketOption(TCP_NoDelay, TRUE)) {
			return false;
		}

		return true;
	}

	bool Socket::Close() {
		if (socket_handle == INVALID_SOCKET) {
			return false;
		}

		int result = closesocket(socket_handle);
		if (result != 0) {
			int error = WSAGetLastError();
			return false;
		}

		socket_handle = INVALID_SOCKET;
		return true;
	}

	bool Socket::Bind(IPEndPoint ip_endpoint) {
		if (ip_version == IPVersion::IPv4) {
			sockaddr_in addr = ip_endpoint.GetSockaddrIPv4();
			int result = bind(socket_handle, (sockaddr*)(&addr), sizeof(sockaddr_in));
			if (result != 0) {
				int error = WSAGetLastError();
				return false;
			}
		}
		else if (ip_version == IPVersion::IPv6) {
			sockaddr_in6 addrv6 = ip_endpoint.GetSockaddrIPv6();
			int result = bind(socket_handle, (sockaddr*)(&addrv6), sizeof(sockaddr_in6));
			if (result != 0) {
				int error = WSAGetLastError();
				return false;
			}
		}

		return true;
	}

	bool Socket::Listen(IPEndPoint ip_endpoint, int backlog) {
		if (ip_version == IPVersion::IPv6) {
			if (!SetSocketOption(SocketOption::IPv6_Only, FALSE))
				return false;
		}

		if (!Bind(ip_endpoint)) {
			return false;
		}

		int result = listen(socket_handle, backlog);
		if (result != 0) {
			int error = WSAGetLastError();
			return false;
		}

		return true;
	}

	bool Socket::Accept(Socket& out_socket) {
		if (ip_version == IPVersion::IPv4) {
			sockaddr_in addr = {};
			int len = sizeof(sockaddr_in);

			SocketHandle accepted_socket_handle = accept(socket_handle, (sockaddr*)(&addr), &len);
			if (accepted_socket_handle == INVALID_SOCKET) {
				int error = WSAGetLastError();
				return false;
			}

			out_socket = Socket(IPVersion::IPv4, accepted_socket_handle);
		}
		else if (ip_version == IPVersion::IPv6) {
			sockaddr_in6 addrv6 = {};
			int len = sizeof(sockaddr_in6);

			SocketHandle accepted_socket_handle = accept(socket_handle, (sockaddr*)(&addrv6), &len);
			if (accepted_socket_handle == INVALID_SOCKET) {
				int error = WSAGetLastError();
				return false;
			}

			out_socket = Socket(IPVersion::IPv6, accepted_socket_handle);
		}

		return true;
	}

	bool Socket::Connect(IPEndPoint ip_endpoint) {
		if (ip_version == IPVersion::IPv4) {
			sockaddr_in addr = ip_endpoint.GetSockaddrIPv4();
			int result = connect(socket_handle, (sockaddr*)(&addr), sizeof(sockaddr_in));
			if (result != 0) {
				int error = WSAGetLastError();
				return false;
			}
		}
		else if (ip_version == IPVersion::IPv6) {
			sockaddr_in6 addrv6 = ip_endpoint.GetSockaddrIPv6();
			int result = connect(socket_handle, (sockaddr*)(&addrv6), sizeof(sockaddr_in6));
			if (result != 0) {
				int error = WSAGetLastError();
				return false;
			}
		}

		return true;
	}

	bool Socket::Send(const void* data, int bytes, int& sent_bytes) {
		sent_bytes = send(socket_handle, (const char*)data, bytes, NULL);
		if (sent_bytes == SOCKET_ERROR) {
			int error = WSAGetLastError();
			return false;
		}

		return true;
	}

	bool Socket::Recv(void* destination, int bytes, int& received_bytes) {
		received_bytes = recv(socket_handle, (char*)destination, bytes, NULL);
		if (received_bytes == 0) {
			return false;
		}
		else if (received_bytes == SOCKET_ERROR) {
			int error = WSAGetLastError();
			return false;
		}

		return true;
	}

	bool Socket::SendAll(const void* data, int bytes) {
		int total_sent_bytes = 0;
		while (total_sent_bytes < bytes) {
			int remaining_bytes = bytes - total_sent_bytes;
			int sent_bytes = 0;
			char* offset = (char*)data + total_sent_bytes;
			if (!Send(offset, remaining_bytes, sent_bytes)) {
				return false;
			}
			total_sent_bytes += sent_bytes;
		}

		return true;
	}

	bool Socket::RecvAll(void* destination, int bytes) {
		int total_received_bytes = 0;
		while (total_received_bytes < bytes) {
			int remaining_bytes = bytes - total_received_bytes;
			int received_bytes = 0;
			char* offset = (char*)destination + total_received_bytes;
			if (!Recv(offset, remaining_bytes, received_bytes)) {
				return false;
			}
			total_received_bytes += received_bytes;
		}

		return true;
	}

	bool Socket::Send(Packet& packet) {
		uint16_t encoded_packet_size = htons(packet.buffer.size());
		if (!SendAll(&encoded_packet_size, sizeof(uint16_t))) {
			return false;
		}
		if (!SendAll(packet.buffer.data(), packet.buffer.size())) {
			return false;
		}

		return true;
	}

	bool Socket::Recv(Packet& packet) {
		packet.Clear();
		uint16_t encoded_packet_size = 0;
		if (!RecvAll(&encoded_packet_size, sizeof(uint16_t))) {
			return false;
		}
		uint16_t buffer_size = ntohs(encoded_packet_size);
		if (buffer_size > MAX_PACKET_SIZE) {
			return false;
		}
		packet.buffer.resize(buffer_size);
		if (!RecvAll(&packet.buffer[0], buffer_size)) {
			return false;
		}

		return true;
	}

#pragma endregion

}
