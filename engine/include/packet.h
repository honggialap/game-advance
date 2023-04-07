#pragma once
#ifndef __ENGINE_PACKET_H__
#define __ENGINE_PACKET_H__

#include "common.h"

enum PacketType : uint16_t {
	Invalid,
	Welcome,
	NotWelcome,
	Ping,
	PlayerConfirm,
	StartGame,
	LocalPlayerSpawn,
	RemotePlayerSpawn,
	PlayerMove,
};

class Packet {
public:
	std::vector<char> buffer;
	uint32_t offset;

	Packet(PacketType packet_type = PacketType::Invalid);

	PacketType GetPacketType();
	void AssignPacketType(PacketType packet_type);

	void Clear();
	void Append(const void* data, uint32_t size);

	Packet& operator << (uint32_t data);
	Packet& operator >> (uint32_t& data);

	Packet& operator << (int32_t data);
	Packet& operator >> (int32_t& data);

	Packet& operator << (const std::string& data);
	Packet& operator >> (std::string& data);

	Packet& operator << (float data);
	Packet& operator >> (float& data);

	Packet& operator << (bool data);
	Packet& operator >> (bool& data);
};

class PacketException {
private:
	std::string exception;

public:
	PacketException(std::string exception)
		: exception(exception) {
	}

	const char* what() { return exception.c_str(); }
	std::string ToString() { return exception; }
};

#endif // !__ENGINE_PACKET_H__
