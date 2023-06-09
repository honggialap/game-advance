#include "engine/networks/packet_manager.h"

namespace NSEngine {
	namespace NSNetworks {

		void CPacketManager::Clear() {
			packets = std::queue<std::shared_ptr<CPacket>>{};
		}

		bool CPacketManager::HasPending() {
			return (!packets.empty());
		}

		void CPacketManager::Append(std::shared_ptr<CPacket> packet) {
			packets.push(std::move(packet));
		}

		std::shared_ptr<CPacket> CPacketManager::Retrive() {
			std::shared_ptr<CPacket> packet = packets.front();
			return packet;
		}

		void CPacketManager::Pop() {
			packets.pop();
		}

	}
}