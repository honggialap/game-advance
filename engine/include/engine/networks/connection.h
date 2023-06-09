#pragma once
#ifndef __ENGINE__NETWORKS__CONNECTION_H__
#define __ENGINE__NETWORKS__CONNECTION_H__

#include "engine/common.h"

#include "engine/networks/socket.h"
#include "engine/networks/packet_manager.h"

namespace NSEngine {
	namespace NSNetworks {

		class CConnection {
		private:
			CIPEndPoint ip_endpoint;

		public:
			CSocket socket;
			char buffer[MAX_PACKET_SIZE];
			CPacketManager imcomming_packets;
			CPacketManager outgoing_packets;

			CConnection();
			CConnection(CSocket socket, CIPEndPoint ip_endpoint);
			void Close();
		};

	}
}

#endif // !__ENGINE__NETWORKS__CONNECTION_H__
