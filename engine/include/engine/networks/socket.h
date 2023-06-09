#pragma once
#ifndef __ENGINE__NETWORKS__SOCKET_H__
#define __ENGINE__NETWORKS__SOCKET_H__

#include "engine/common.h"

#include "engine/networks/ip_endpoint.h"
#include "engine/networks/packet.h"

namespace NSEngine {
	namespace NSNetworks {

		typedef SOCKET SocketHandle;

		enum ESocketOption {
			TCP_NoDelay,
			IPv6_Only
		};

		class CSocket {
		private:
			EIPVersion ip_version = EIPVersion::IPv4;
			SocketHandle socket_handle = INVALID_SOCKET;

		public:
			EIPVersion GetIPVersion() { return ip_version; }
			SocketHandle GetSocketHandle() { return socket_handle; }

		public:
			CSocket(
				EIPVersion ip_version = EIPVersion::IPv4,
				SocketHandle socket_handle = INVALID_SOCKET
			);

		private:
			bool SetSocketOption(ESocketOption socket_option, BOOL value);

		public:
			bool SetSocketBlocking(bool is_blocking);

			bool Create();
			bool Close();

			bool Bind(CIPEndPoint ip_endpoint);
			bool Listen(CIPEndPoint ip_endpoint, int backlog = 5);
			bool Accept(CSocket& out_socket, CIPEndPoint* ip_endpoint = nullptr);
			bool Connect(CIPEndPoint ip_endpoint);

			bool Send(const void* data, int bytes, int& sent_bytes);
			bool Recv(void* destination, int bytes, int& received_bytes);

			bool SendAll(const void* data, int bytes);
			bool RecvAll(void* destination, int bytes);

			bool Send(CPacket& packet);
			bool Recv(CPacket& packet);
		};

	}
}

#endif // !__ENGINE__NETWORKS__SOCKET_H__
