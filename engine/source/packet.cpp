#include "packet.h"

namespace Engine {
	Packet::Packet(PacketType packet_type) {
		Clear();
		AssignPacketType(packet_type);
	}

	PacketType Packet::GetPacketType() {
		PacketType* packet_type_ptr = reinterpret_cast<PacketType*>(&buffer[0]);
		return static_cast<PacketType>(ntohs(*packet_type_ptr));
	}

	void Packet::AssignPacketType(PacketType packet_type) {
		PacketType* packet_type_ptr = reinterpret_cast<PacketType*>(&buffer[0]);
		*packet_type_ptr = static_cast<PacketType>(htons(packet_type));
	}

	void Packet::Clear() {
		buffer.resize(sizeof(PacketType));
		AssignPacketType(PacketType::Invalid);
		offset = sizeof(PacketType);
	}

	void Packet::Append(const void* data, uint32_t size) {
		if ((buffer.size() + size) > MAX_PACKET_SIZE) {
			throw PacketException("[Packet::Append(const void*, uint32_t)] - Packet size exceeded max packet size.");
		}

		buffer.insert(buffer.end(), (char*)data, (char*)data + size);
	}

	Packet& Packet::operator<<(uint32_t data) {
		data = htonl(data);
		Append(&data, sizeof(uint32_t));
		return *this;
	}

	Packet& Packet::operator>>(uint32_t& data) {
		if ((offset + sizeof(uint32_t)) > buffer.size()) {
			throw PacketException("[Packet::operator>>(uint32_t&)] - Extraction offset exceeded buffer size.");
		}

		data = *reinterpret_cast<uint32_t*>(&buffer[offset]);
		data = ntohl(data);
		offset += sizeof(uint32_t);
		return *this;
	}

	Packet& Packet::operator<<(const std::string& data) {
		*this << (uint32_t)data.size();
		Append(data.data(), data.size());
		return *this;
	}

	Packet& Packet::operator>>(std::string& data) {
		data.clear();
		uint32_t string_size = 0;
		*this >> string_size;

		if ((offset + sizeof(uint32_t)) > string_size) {
			throw PacketException("[Packet::operator>>(std::string&)] - Extraction offset exceeded buffer size.");
		}

		data.resize(string_size);
		data.assign(&buffer[offset], string_size);
		offset += string_size;
		return *this;
	}

}
