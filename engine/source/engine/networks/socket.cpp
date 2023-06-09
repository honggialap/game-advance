#include "engine/networks/socket.h"

namespace NSEngine {
	namespace NSNetworks {

		CSocket::CSocket(EIPVersion ip_version, SocketHandle socket_handle)
			: ip_version(ip_version), socket_handle(socket_handle) {
		}

		bool CSocket::SetSocketOption(ESocketOption socket_option, BOOL value) {
			int result = 0;
			switch (socket_option)
			{
			case ESocketOption::TCP_NoDelay:
				result = setsockopt(
					socket_handle,
					IPPROTO_TCP,
					TCP_NODELAY,
					(const char*)&value
					, sizeof(value)
				);
				break;

			case ESocketOption::IPv6_Only:
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

		bool CSocket::SetSocketBlocking(bool is_blocking) {
			unsigned long non_blocking = 1;
			unsigned long blocking = 0;
			int result = ioctlsocket(socket_handle, FIONBIO, is_blocking ? &blocking : &non_blocking);
			if (result == SOCKET_ERROR) {
				int error = WSAGetLastError();
				return false;
			}

			return true;
		}

		bool CSocket::Create() {
			if (socket_handle != INVALID_SOCKET) {
				return false;
			}

			socket_handle = socket((ip_version == EIPVersion::IPv4) ? AF_INET : AF_INET6, SOCK_STREAM, IPPROTO_TCP);
			if (socket_handle == INVALID_SOCKET) {
				int error = WSAGetLastError();
				return false;
			}

			if (!SetSocketOption(TCP_NoDelay, TRUE)) {
				return false;
			}

			return true;
		}

		bool CSocket::Close() {
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

		bool CSocket::Bind(CIPEndPoint ip_endpoint) {
			if (ip_version == EIPVersion::IPv4) {
				sockaddr_in addr = ip_endpoint.GetSockaddrIPv4();
				int result = bind(socket_handle, (sockaddr*)(&addr), sizeof(sockaddr_in));
				if (result != 0) {
					int error = WSAGetLastError();
					return false;
				}
			}
			else if (ip_version == EIPVersion::IPv6) {
				sockaddr_in6 addrv6 = ip_endpoint.GetSockaddrIPv6();
				int result = bind(socket_handle, (sockaddr*)(&addrv6), sizeof(sockaddr_in6));
				if (result != 0) {
					int error = WSAGetLastError();
					return false;
				}
			}

			return true;
		}

		bool CSocket::Listen(CIPEndPoint ip_endpoint, int backlog) {
			if (ip_version == EIPVersion::IPv6) {
				if (!SetSocketOption(ESocketOption::IPv6_Only, FALSE))
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

		bool CSocket::Accept(CSocket& out_socket, CIPEndPoint* ip_endpoint) {
			if (ip_version == EIPVersion::IPv4) {
				sockaddr_in addr = {};
				int len = sizeof(sockaddr_in);

				SocketHandle accepted_socket_handle = accept(socket_handle, (sockaddr*)(&addr), &len);
				if (accepted_socket_handle == INVALID_SOCKET) {
					int error = WSAGetLastError();
					return false;
				}

				if (ip_endpoint != nullptr) {
					*ip_endpoint = CIPEndPoint((sockaddr*)&addr);
				}

				out_socket = CSocket(EIPVersion::IPv4, accepted_socket_handle);
			}
			else if (ip_version == EIPVersion::IPv6) {
				sockaddr_in6 addrv6 = {};
				int len = sizeof(sockaddr_in6);

				SocketHandle accepted_socket_handle = accept(socket_handle, (sockaddr*)(&addrv6), &len);
				if (accepted_socket_handle == INVALID_SOCKET) {
					int error = WSAGetLastError();
					return false;
				}

				if (ip_endpoint != nullptr) {
					*ip_endpoint = CIPEndPoint((sockaddr*)&addrv6);
				}

				out_socket = CSocket(EIPVersion::IPv6, accepted_socket_handle);
			}

			return true;
		}

		bool CSocket::Connect(CIPEndPoint ip_endpoint) {
			if (ip_version == EIPVersion::IPv4) {
				sockaddr_in addr = ip_endpoint.GetSockaddrIPv4();
				int result = connect(socket_handle, (sockaddr*)(&addr), sizeof(sockaddr_in));
				if (result != 0) {
					int error = WSAGetLastError();
					return false;
				}
			}
			else if (ip_version == EIPVersion::IPv6) {
				sockaddr_in6 addrv6 = ip_endpoint.GetSockaddrIPv6();
				int result = connect(socket_handle, (sockaddr*)(&addrv6), sizeof(sockaddr_in6));
				if (result != 0) {
					int error = WSAGetLastError();
					return false;
				}
			}

			return true;
		}

		bool CSocket::Send(const void* data, int bytes, int& sent_bytes) {
			sent_bytes = send(socket_handle, (const char*)data, bytes, NULL);
			if (sent_bytes == SOCKET_ERROR) {
				int error = WSAGetLastError();
				return false;
			}

			return true;
		}

		bool CSocket::Recv(void* destination, int bytes, int& received_bytes) {
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

		bool CSocket::SendAll(const void* data, int bytes) {
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

		bool CSocket::RecvAll(void* destination, int bytes) {
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

		bool CSocket::Send(CPacket& packet) {
			uint16_t encoded_packet_size = htons(packet.buffer.size());
			if (!SendAll(&encoded_packet_size, sizeof(uint16_t))) {
				return false;
			}
			if (!SendAll(packet.buffer.data(), packet.buffer.size())) {
				return false;
			}

			return true;
		}

		bool CSocket::Recv(CPacket& packet) {
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

	}
}
