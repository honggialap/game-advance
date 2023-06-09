#pragma once
#ifndef __SERVER__NETWORKS__SERVER_H__
#define __SERVER__NETWORKS__SERVER_H__

#include "engine/common.h"
#include "engine/networks/connection.h"

namespace NSServer {
	namespace NSNetworks {

		class CServer {
		protected:
			std::mutex mutex;

			bool is_initialized = false;
			WSADATA wsa_data;

			bool is_listening = false;
			NSEngine::NSNetworks::CSocket listening_socket;
			WSAPOLLFD listening_master_fd;
			NSEngine::NSNetworks::CIPEndPoint host_address;
			uint32_t max_connection_count = 0;

			std::map<uint32_t, std::tuple<NSEngine::NSNetworks::CConnection, WSAPOLLFD, bool>> connections;
			uint32_t client_id = 1000;

		public:
			void SetHostAddress(NSEngine::NSNetworks::CIPEndPoint value);
			NSEngine::NSNetworks::CIPEndPoint GetHostAddress();

			void SetMaxConnectionLimit(uint32_t value);
			uint32_t GetMaxConnectionLimit();

			bool Initialize();
			bool Shutdown();

			bool StartListen();
			bool StopListen();

			bool Accept(uint32_t id, NSEngine::NSNetworks::CConnection connection, WSAPOLLFD connection_master_fd);
			bool Disconnect(uint32_t id);

			bool ProcessNetworks();
			bool ProcessPackets();

			bool Send(uint32_t id, std::shared_ptr<NSEngine::NSNetworks::CPacket> packet);
			bool SendAll(std::shared_ptr<NSEngine::NSNetworks::CPacket> packet);
			bool SendAllExcept(uint32_t id, std::shared_ptr<NSEngine::NSNetworks::CPacket> packet);
			virtual bool ProcessPacket(std::shared_ptr<NSEngine::NSNetworks::CPacket> packet) = 0;

			virtual void OnConnect(uint32_t connection_id) = 0;
			virtual void OnDisconnect(uint32_t connection_id) = 0;
		};

	}
}

#endif // !__SERVER__NETWORKS__SERVER_H__
