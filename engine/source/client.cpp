#include "client.h"

namespace Engine {

	bool Client::Connect(IPEndPoint ip_endpoint) {
		is_connecting = false;

		int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
		if (result != 0) {
			return false;
		}

		if (LOBYTE(wsa_data.wVersion) != 2 || HIBYTE(wsa_data.wVersion) != 2) {
			return false;
		}

		Socket connection_socket = Socket(ip_endpoint.GetIPVersion());
		if (!connection_socket.Create()) {
			return false;
		}

		if (!connection_socket.SetSocketBlocking(true)) {
			return false;
		}

		if (!connection_socket.Connect(ip_endpoint)) {
			connection_socket.Close();
			OnConnectFail();
			return false;
		}

		if (!connection_socket.SetSocketBlocking(false)) {
			return false;
		}

		connection = Connection(connection_socket, ip_endpoint);

		master_fd.fd = connection.socket.GetSocketHandle();
		master_fd.events = POLLRDNORM;
		master_fd.revents = 0;
		is_connecting = true;
		OnConnect();
		return true;
	}

	void Client::CleanUp() {
		WSACleanup();
	}

	bool Client::ProcessNetworks() {
		if (connection.outgoing_packets.HasPending()) {
			master_fd.events = POLLRDNORM | POLLWRNORM;
		}

		temp_fd = master_fd;

		if (WSAPoll(&temp_fd, 1, 1) > 0) {

			// Error
			if (temp_fd.revents & POLLERR) {
				CloseConnection();
				return false;
			}
			if (temp_fd.revents & POLLHUP) {
				CloseConnection();
				return false;
			}
			if (temp_fd.revents & POLLNVAL) {
				CloseConnection();
				return false;
			}
			// End of Error

			// Read
			if (temp_fd.revents & POLLRDNORM) {
				PacketManager& incomming = connection.imcomming_packets;
				int received_bytes = 0;
				if (incomming.packet_process_task == PacketProcessTask::Header) {
					received_bytes = recv(
						temp_fd.fd,
						(char*)&incomming.packet_size + incomming.extraction_offset,
						sizeof(uint16_t) - incomming.extraction_offset,
						0
					);
				}
				else {
					received_bytes = recv(
						temp_fd.fd,
						(char*)&connection.buffer + incomming.extraction_offset,
						incomming.packet_size - incomming.extraction_offset,
						0
					);
				}

				if (received_bytes == 0) {
					CloseConnection();
					return false;
				}

				if (received_bytes == SOCKET_ERROR) {
					int error = WSAGetLastError();
					if (error != WSAEWOULDBLOCK) {
						CloseConnection();
						return false;
					}
				}

				if (received_bytes > 0) {
					incomming.extraction_offset += received_bytes;
					if (incomming.packet_process_task == PacketProcessTask::Header) {
						if (incomming.extraction_offset == sizeof(uint16_t)) {
							incomming.packet_size = ntohs(incomming.packet_size);
							if (incomming.packet_size > MAX_PACKET_SIZE) {
								CloseConnection();
								return false;
							}
							incomming.extraction_offset = 0;
							incomming.packet_process_task = PacketProcessTask::Body;
						}
					}
					else {
						if (incomming.extraction_offset == incomming.packet_size) {
							std::shared_ptr<Packet> packet = std::make_shared<Packet>();
							packet->buffer.resize(incomming.packet_size);
							memcpy(&packet->buffer[0], connection.buffer, incomming.packet_size);

							incomming.Append(packet);

							incomming.packet_size = 0;
							incomming.extraction_offset = 0;
							incomming.packet_process_task = PacketProcessTask::Header;
						}
					}
				}
			}
			// End of Read

			// Write
			if (temp_fd.revents & POLLWRNORM) {
				PacketManager& outgoing = connection.outgoing_packets;
				while (outgoing.HasPending()) {
					if (outgoing.packet_process_task == PacketProcessTask::Header) {
						outgoing.packet_size = outgoing.Retrive()->buffer.size();
						uint16_t packet_size = htons(outgoing.packet_size);
						int sent_bytes = send(
							temp_fd.fd,
							(char*)(&packet_size) + outgoing.extraction_offset,
							sizeof(uint16_t) - outgoing.extraction_offset,
							0
						);

						if (sent_bytes > 0) {
							outgoing.extraction_offset += sent_bytes;
						}

						if (sent_bytes == sizeof(uint16_t)) {
							outgoing.extraction_offset = 0;
							outgoing.packet_process_task = PacketProcessTask::Body;
						}
						else {
							break;
						}
					}
					else {
						char* buffer = &outgoing.Retrive()->buffer[0];
						int sent_bytes = send(
							temp_fd.fd,
							(char*)(buffer)+outgoing.extraction_offset,
							outgoing.packet_size - outgoing.extraction_offset,
							0
						);

						if (sent_bytes > 0) {
							outgoing.extraction_offset += sent_bytes;
						}

						if (outgoing.extraction_offset == outgoing.packet_size) {
							outgoing.extraction_offset = 0;
							outgoing.packet_process_task = PacketProcessTask::Header;
							outgoing.Pop();
						}
						else {
							break;
						}
					}
				}

				if (!outgoing.HasPending()) {
					master_fd.events = POLLRDNORM;
				}

			}
			// End of Write
		}

		while (connection.imcomming_packets.HasPending()) {
			std::shared_ptr<Packet> packet = connection.imcomming_packets.Retrive();
			if (!ProcessPacket(packet)) {
				CloseConnection();
				return false;
			}
			connection.imcomming_packets.Pop();
		}

		return true;
	}

	void Client::CloseConnection() {
		OnDisconnect();
		master_fd.fd = 0;
		is_connecting = false;
		connection.Close();
	}

	bool Client::ProcessPacket(std::shared_ptr<Packet> packet) {
		switch (packet->GetPacketType())
		{
		case Engine::ChatMessage: {
			std::string message;
			*packet >> message;
			std::cout << message << std::endl;
			break;
		}

		case Engine::IntArray: {
			uint32_t array_size = 0;
			*packet >> array_size;
			std::cout << "Array size: " << array_size << std::endl;
			for (uint32_t it = 0; it < array_size; it++) {
				uint32_t element = 0;
				*packet >> element;
				std::cout << "Element[" << it << "] - " << element << std::endl;
			}
			break;
		}

		case Engine::Invalid:
		default:
			return false;
		}
		return true;
	}

}