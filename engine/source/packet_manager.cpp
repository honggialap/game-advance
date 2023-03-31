#include "packet_manager.h"

void PacketManager::Clear() {
	packets = std::queue<std::shared_ptr<Packet>>{};
}

bool PacketManager::HasPending() {
	return (!packets.empty());
}

void PacketManager::Append(std::shared_ptr<Packet> packet) {
	packets.push(std::move(packet));
}

std::shared_ptr<Packet> PacketManager::Retrive() {
	std::shared_ptr<Packet> packet = packets.front();
	return packet;
}

void PacketManager::Pop() {
	packets.pop();
}
