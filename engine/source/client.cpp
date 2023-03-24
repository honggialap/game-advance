#include "client.h"

namespace Engine {

	bool Client::Initialize() {
		if (is_initialized) {
			printf("[Client::Initialize()] - Function called while networks have been initialized.\n");
			return false;
		}

		if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
			printf("[Client::Initialize()] - WSAStartup failed with error code: %d.\n", WSAGetLastError());
			return false;
		}

		is_initialized = true;
		printf("[Client::Initialize()] - Success.\n");
		return true;
	}

	bool Client::Shutdown() {
		if (!is_initialized) {
			printf("[Client::Shutdown()] - Function called while networks have not been initialized.\n");
			return false;
		}

		if (WSACleanup() != 0) {
			printf("[Client::Shutdown()] - WSACleanup failed with error code: %d.\n", WSAGetLastError());
			return true;
		}

		is_initialized = false;
		printf("[Client::Shutdown()] - Success.\n");
		return true;
	}

	bool Client::Connect(IPEndPoint ip_endpoint) {
		if (!is_initialized) {
			printf("[Client::Connect(IPEndPoint)] - Function called while networks have not been initialized.\n");
			return false;
		}

		if (is_connecting) {
			printf("[Client::Connect(IPEndPoint)] - Function called while being connected.\n");
			return false;
		}

		Socket connection_socket = Socket(ip_endpoint.GetIPVersion());
		if (!connection_socket.Create()) {
			printf("[Client::Connect(IPEndPoint)] - Failed to create connection socket.\n");
			return false;
		}

		if (!connection_socket.SetSocketBlocking(true)) {
			printf("[Client::Connect(IPEndPoint)] - Failed to set connection socket blocking option pre-connecting.\n");
			return false;
		}

		if (!connection_socket.Connect(ip_endpoint)) {
			connection_socket.Close();
			OnConnectFail();
			printf("[Client::Connect(IPEndPoint)] - Failed to connect to server.\n");
			return false;
		}

		if (!connection_socket.SetSocketBlocking(false)) {
			connection_socket.Close();
			OnConnectFail();
			printf("[Client::Connect(IPEndPoint)] - Failed to set connection socket blocking option post-connecting.\n");
			return false;
		}

		connection = Connection(connection_socket, ip_endpoint);

		master_fd.fd = connection.socket.GetSocketHandle();
		master_fd.events = POLLRDNORM;
		master_fd.revents = 0;

		is_connecting = true;
		OnConnect();
		printf("[Client::Connect(IPEndPoint)] - Success.\n");
		return true;
	}

	bool Client::Disconnect() {
		if (!is_initialized) {
			printf("[Client::Disconnect()] - Function called while networks have not been initialized.\n");
			return false;
		}

		if (!is_connecting) {
			printf("[Client::Disconnect()] - Function called while not being connected.\n");
			return false;
		}

		master_fd.fd = 0;
		connection.Close();

		is_connecting = false;
		OnDisconnect();
		printf("[Client::Disconnect()] - Success.\n");
		return true;
	}

	bool Client::ProcessNetworks() {
		if (!is_initialized) {
			printf("[Client::ProcessNetworks()] - Function called while networks have not been initialized.\n");
			return false;
		}

		if (!is_connecting) {
			printf("[Client::ProcessNetworks()] - Function called while not being connected.\n");
			return false;
		}


		if (connection.outgoing_packets.HasPending()) {
			master_fd.events = POLLRDNORM | POLLWRNORM;
		}

		temp_fd = master_fd;

		if (WSAPoll(&temp_fd, 1, 1) > 0) {

			// Error
			if (temp_fd.revents & POLLERR) {
				Disconnect();
				return false;
			}
			if (temp_fd.revents & POLLHUP) {
				Disconnect();
				return false;
			}
			if (temp_fd.revents & POLLNVAL) {
				Disconnect();
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
					Disconnect();
					return false;
				}

				if (received_bytes == SOCKET_ERROR) {
					int error = WSAGetLastError();
					if (error != WSAEWOULDBLOCK) {
						Disconnect();
						return false;
					}
				}

				if (received_bytes > 0) {
					incomming.extraction_offset += received_bytes;
					if (incomming.packet_process_task == PacketProcessTask::Header) {
						if (incomming.extraction_offset == sizeof(uint16_t)) {
							incomming.packet_size = ntohs(incomming.packet_size);
							if (incomming.packet_size > MAX_PACKET_SIZE) {
								Disconnect();
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
				Disconnect();
				return false;
			}
			connection.imcomming_packets.Pop();
		}

		return true;
	}

}