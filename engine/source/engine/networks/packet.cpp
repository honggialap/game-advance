#include "engine/networks/packet.h"

namespace NSEngine {
	namespace NSNetworks {

		CPacket::CPacket(EPacketType packet_type) {
			Clear();
			AssignPacketType(packet_type);
		}

		EPacketType CPacket::GetPacketType() {
			EPacketType* packet_type_ptr = reinterpret_cast<EPacketType*>(&buffer[0]);
			return static_cast<EPacketType>(ntohs(*packet_type_ptr));
		}

		void CPacket::AssignPacketType(EPacketType packet_type) {
			EPacketType* packet_type_ptr = reinterpret_cast<EPacketType*>(&buffer[0]);
			*packet_type_ptr = static_cast<EPacketType>(htons(packet_type));
		}

		void CPacket::Clear() {
			buffer.resize(sizeof(EPacketType));
			AssignPacketType(EPacketType::INVALID);
			offset = sizeof(EPacketType);
		}

		void CPacket::Append(const void* data, uint32_t size) {
			if ((buffer.size() + size) > MAX_PACKET_SIZE) {
				throw CPacketException("[Packet::Append(const void*, uint32_t)] - Packet size exceeded max packet size.");
			}

			buffer.insert(buffer.end(), (char*)data, (char*)data + size);
		}

		CPacket& CPacket::operator<<(uint16_t data) {
			data = htons(data);
			Append(&data, sizeof(uint16_t));
			return *this;
		}

		CPacket& CPacket::operator>>(uint16_t& data) {
			if ((offset + sizeof(uint16_t)) > buffer.size()) {
				throw CPacketException("[Packet::operator>>(uint16_t&)] - Extraction offset exceeded buffer size.");
			}

			data = *reinterpret_cast<uint16_t*>(&buffer[offset]);
			data = ntohs(data);
			offset += sizeof(uint16_t);
			return *this;
		}

		CPacket& CPacket::operator<<(int16_t data) {
			data = htons(data);
			Append(&data, sizeof(int16_t));
			return *this;
		}

		CPacket& CPacket::operator>>(int16_t& data) {
			if ((offset + sizeof(int16_t)) > buffer.size()) {
				throw CPacketException("[Packet::operator>>(int16_t&)] - Extraction offset exceeded buffer size.");
			}

			data = *reinterpret_cast<int16_t*>(&buffer[offset]);
			data = ntohs(data);
			offset += sizeof(int16_t);
			return *this;
		}

		CPacket& CPacket::operator<<(uint32_t data) {
			data = htonl(data);
			Append(&data, sizeof(uint32_t));
			return *this;
		}

		CPacket& CPacket::operator>>(uint32_t& data) {
			if ((offset + sizeof(uint32_t)) > buffer.size()) {
				throw CPacketException("[Packet::operator>>(uint32_t&)] - Extraction offset exceeded buffer size.");
			}

			data = *reinterpret_cast<uint32_t*>(&buffer[offset]);
			data = ntohl(data);
			offset += sizeof(uint32_t);
			return *this;
		}

		CPacket& CPacket::operator<<(int32_t data) {
			data = htonl(data);
			Append(&data, sizeof(int32_t));
			return *this;
		}

		CPacket& CPacket::operator>>(int32_t& data) {
			if ((offset + sizeof(int32_t)) > buffer.size()) {
				throw CPacketException("[Packet::operator>>(int32_t&)] - Extraction offset exceeded buffer size.");
			}

			data = *reinterpret_cast<int32_t*>(&buffer[offset]);
			data = ntohl(data);
			offset += sizeof(int32_t);
			return *this;
		}

		CPacket& CPacket::operator<<(const std::string& data) {
			*this << (uint32_t)data.size();
			Append(data.data(), data.size());
			return *this;
		}

		CPacket& CPacket::operator>>(std::string& data) {
			data.clear();
			uint32_t string_size = 0;
			*this >> string_size;

			if ((offset + string_size) > buffer.size()) {
				throw CPacketException("[Packet::operator>>(std::string&)] - Extraction offset exceeded buffer size.");
			}

			data.resize(string_size);
			data.assign(&buffer[offset], string_size);
			offset += string_size;
			return *this;
		}

		CPacket& CPacket::operator<<(float data) {
			//data = htonf(data);
			Append(&data, sizeof(float));
			return *this;
		}

		CPacket& CPacket::operator>>(float& data) {
			if ((offset + sizeof(float)) > buffer.size()) {
				throw CPacketException("[Packet::operator>>(float&)] - Extraction offset exceeded buffer size.");
			}

			data = *reinterpret_cast<float*>(&buffer[offset]);
			//data = ntohf(data);
			offset += sizeof(float);
			return *this;
		}

		CPacket& CPacket::operator<<(bool data) {
			Append(&data, sizeof(bool));
			return *this;
		}

		CPacket& CPacket::operator>>(bool& data) {
			if ((offset + sizeof(bool)) > buffer.size()) {
				throw CPacketException("[Packet::operator>>(bool&)] - Extraction offset exceeded buffer size.");
			}

			data = *reinterpret_cast<bool*>(&buffer[offset]);
			offset += sizeof(bool);
			return *this;
		}

	}
}
