#include "client.h"

bool Client::Initialize(IPEndPoint ip_endpoint) {
	if (is_initialized) {
		printf("[bool Client::Initialize(IPEndPoint)] - Already initialized.\n");
		return false;
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
		printf("[bool Client::Initialize(IPEndPoint)] - WSAStartup failed with error code: %d.\n", WSAGetLastError());
		return false;
	}

	host_address = ip_endpoint;
	is_initialized = true;
	
	printf("[bool Client::Initialize(IPEndPoint)] - Success.\n");
	return true;
}

bool Client::Shutdown() {
	if (!is_initialized) {
		printf("[bool Client::Shutdown()] - Not initialized yet.\n");
		return false;
	}

	if (WSACleanup() != 0) {
		printf("[bool Client::Shutdown()] - WSACleanup failed with error code: %d.\n", WSAGetLastError());
		return true;
	}

	host_address = {};
	is_initialized = false;

	printf("[bool Client::Shutdown()] - Success.\n");
	return true;
}

bool Client::Connect() {
	if (!is_initialized) {
		printf("[bool Client::Connect()] - Not initialized yet.\n");
		return false;
	}

	if (is_connecting) {
		printf("[bool Client::Connect()] - Already connecting.\n");
		return false;
	}

	Socket connection_socket = Socket(host_address.GetIPVersion());
	if (!connection_socket.Create()) {
		printf("[bool Client::Connect()] - Failed to create connection socket.\n");
		return false;
	}

	if (!connection_socket.SetSocketBlocking(true)) {
		printf("[bool Client::Connect()] - Failed to set connection socket blocking option pre-connecting.\n");
		return false;
	}

	if (!connection_socket.Connect(host_address)) {
		connection_socket.Close();
		OnConnectFail();

		printf("[bool Client::Connect()] - Failed to connect to server.\n");
		return false;
	}

	if (!connection_socket.SetSocketBlocking(false)) {
		connection_socket.Close();
		OnConnectFail();

		printf("[bool Client::Connect()] - Failed to set connection socket blocking option post-connecting.\n");
		return false;
	}

	Connection connection = Connection(connection_socket, host_address);

	WSAPOLLFD master_fd = {};
	master_fd.fd = connection.socket.GetSocketHandle();
	master_fd.events = POLLRDNORM;
	master_fd.revents = 0;

	host_connection = std::make_pair(connection, master_fd);

	is_approved = false;
	is_connecting = true;
	OnConnect();

	printf("[bool Client::Connect()] - Success.\n");
	return true;
}

bool Client::Disconnect() {
	if (!is_initialized) {
		printf("[bool Client::Disconnect()] - Not initialized yet.\n");
		return false;
	}

	if (!is_connecting) {
		printf("[bool Client::Disconnect()] - Not connected yet.\n");
		return false;
	}

	host_connection.first.Close();
	host_connection.second = {};

	is_approved = false;
	is_connecting = false;
	OnDisconnect();

	printf("[bool Client::Disconnect()] - Success.\n");
	return true;
}

bool Client::ProcessNetworks() {
	if (!is_initialized) {
		printf("[bool Client::ProcessNetworks()] - Not initialized yet.\n");
		return false;
	}

	if (!is_connecting) {
		printf("[bool Client::ProcessNetworks()] - Not connected yet.\n");
		return false;
	}

	Connection& connection = host_connection.first;
	WSAPOLLFD& master_fd = host_connection.second;

	if (connection.outgoing_packets.HasPending()) {
		master_fd.events = POLLRDNORM | POLLWRNORM;
	}

	WSAPOLLFD temp_fd = master_fd;

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

bool Client::Send(std::shared_ptr<Packet> packet) {
	if (!is_initialized) {
		printf("[bool Client::Send(std::shared_ptr<Packet>)] - Not initialized yet.\n");
		return false;
	}

	if (!is_connecting) {
		printf("[bool Client::Send(std::shared_ptr<Packet>)] - Not connected yet.\n");
		return false;
	}

	host_connection.first.outgoing_packets.Append(packet);
	return true;
}
