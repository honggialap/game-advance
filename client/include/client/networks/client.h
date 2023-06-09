#pragma once
#ifndef __CLIENT__NETWORKS__CLIENT_H__
#define __CLIENT__NETWORKS__CLIENT_H__

#include "engine/common.h"
#include "engine/networks/connection.h"

namespace NSClient {
	namespace NSNetworks {

		class CClient {
		protected:
			std::mutex								mutex;

			bool									is_initialized = false;
			WSADATA									wsa_data;

			bool									is_connecting = false;
			NSEngine::NSNetworks::CIPEndPoint		host_address;
			NSEngine::NSNetworks::CConnection		connection;
			WSAPOLLFD								master_fd;

			bool									is_accepted = false;
			uint32_t								client_id = 0;

		public:
			void SetHostAddress(NSEngine::NSNetworks::CIPEndPoint value);
			NSEngine::NSNetworks::CIPEndPoint GetHostAddress();

			void AssignClientId(uint32_t value);
			uint32_t GetClientId();

			bool Initialize();
			bool Shutdown();

			bool Connect();
			bool Disconnect();

			bool ProcessNetworks();
			bool ProcessPackets();

			bool Send(std::shared_ptr<NSEngine::NSNetworks::CPacket> packet);
			virtual bool ProcessPacket(std::shared_ptr<NSEngine::NSNetworks::CPacket> packet) = 0;

			virtual void OnConnect() = 0;
			virtual void OnDisconnect() = 0;
			virtual void OnConnectFail() = 0;
		};

	}
}

#endif // !__CLIENT__NETWORKS__CLIENT_H__
