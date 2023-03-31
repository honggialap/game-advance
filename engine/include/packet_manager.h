#pragma once
#ifndef __ENGINE_PACKETMANAGER_H__
#define __ENGINE_PACKETMANAGER_H__

#include "common.h"
#include "packet.h"

enum PacketProcessTask {
	Header,
	Body
};

class PacketManager {
private:
	std::queue<std::shared_ptr<Packet>> packets;

public:
	uint16_t packet_size;
	int extraction_offset;
	PacketProcessTask packet_process_task = PacketProcessTask::Header;

public:
	void Clear();
	bool HasPending();
	void Append(std::shared_ptr<Packet> packet);
	std::shared_ptr<Packet> Retrive();
	void Pop();
};

#endif // !__ENGINE_PACKETMANAGER_H__
