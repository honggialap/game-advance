#pragma once
#ifndef __ENGINE__NETWORKS__PACKET_MANAGER_H__
#define __ENGINE__NETWORKS__PACKET_MANAGER_H__

#include "engine/common.h"

#include "engine/networks/packet.h"

namespace NSEngine {
	namespace NSNetworks {

		enum EPacketProcessTask {
			Header,
			Body
		};

		class CPacketManager {
		private:
			std::queue<std::shared_ptr<CPacket>> packets;

		public:
			uint16_t packet_size;
			int extraction_offset;
			EPacketProcessTask packet_process_task = EPacketProcessTask::Header;

		public:
			void Clear();
			bool HasPending();
			void Append(std::shared_ptr<CPacket> packet);
			std::shared_ptr<CPacket> Retrive();
			void Pop();
		};

	}
}

#endif // !__ENGINE__NETWORKS__PACKET_MANAGER_H__
