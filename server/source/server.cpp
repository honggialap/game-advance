#include "server.h"

bool Server::Initialize() {
	if (is_initialized) {
		printf("[bool Server::Initialize()] - Function called while networks have been initialized.\n");
		return false;
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
		printf("[bool Server::Initialize()] - WSAStartup failed with error code: %d.\n", WSAGetLastError());
		return false;
	}

	is_initialized = true;
	printf("[bool Server::Initialize()] - Success.\n");
	return true;
}

bool Server::Shutdown() {
	if (!is_initialized) {
		printf("[bool Server::Shutdown()] - Function called while networks have not been initialized.\n");
		return false;
	}

	if (WSACleanup() != 0) {
		printf("[bool Server::Shutdown()] - WSACleanup failed with error code: %d.\n", WSAGetLastError());
		return true;
	}

	is_initialized = false;
	printf("[bool Server::Shutdown()] - Success.\n");
	return true;
}

bool Server::StartListening(IPEndPoint ip_endpoint, uint32_t connection_count) {
	if (!is_initialized) {
		printf("[bool Server::StartListening(IPEndPoint, uint32_t)] - Function called while networks have not been initialized.\n");
		return false;
	}

	if (is_listening) {
		printf("[bool Server::StartListening(IPEndPoint, uint32_t)] - Function called while being listening.\n");
		return false;
	}

	Socket listening_socket = Socket(IPVersion::IPv6);
	if (!listening_socket.Create()) {
		printf("[bool Server::StartListening(IPEndPoint, uint32_t)] - Failed to create listening socket.\n");
		return false;
	}

	if (!listening_socket.SetSocketBlocking(false)) {
		listening_socket.Close();
		printf("[bool StartListening(IPEndPoint, uint32_t)] - Failed to set listening socket blocking.\n");
		return false;
	}

	if (!listening_socket.Listen(ip_endpoint)) {
		listening_socket.Close();
		printf("[bool StartListening(IPEndPoint, uint32_t)] - Failed to listen for connection.\n");
		return false;
	}

	WSAPOLLFD listening_master_fd = {};
	listening_master_fd.fd = listening_socket.GetSocketHandle();
	listening_master_fd.events = POLLRDNORM;
	listening_master_fd.revents = 0;

	listener = std::make_pair(listening_socket, listening_master_fd);
	max_connection_count = connection_count;

	is_listening = true;
	printf("[bool StartListening(IPEndPoint, uint32_t)] - Success.\n");
	return true;
}

bool Server::StopListening() {
	if (!is_initialized) {
		printf("[bool Server::StopListening()] - Function called while networks have not been initialized.\n");
		return false;
	}

	if (!is_listening) {
		printf("[bool Server::StopListening()] - Function called while not being listening.\n");
		return false;
	}

	listener.first.Close();
	listener.second = {};

	is_listening = false;
	printf("[bool Server::StopListening()] - Function called while not being listening.\n");
	return true;
}

bool Server::Listening() {
	if (!is_initialized) {
		printf("[Server::Listening()] - Function called while networks have not been initialized.\n");
		return false;
	}

	if (!is_listening) {
		printf("[Server::Listening()] - Function called while not being listening.\n");
		return false;
	}

	if (connections.size() >= max_connection_count) {
		printf("[Server::Listening()] - Max connection count accepted.\n");
		return false;
	}

	WSAPOLLFD listening_temp_fd = listener.second;
	Socket& listening_socket = listener.first;

	if (WSAPoll(&listening_temp_fd, 1, 1) > 0) {
		if (listening_temp_fd.revents & POLLRDNORM) {
			Socket new_connection_socket;
			IPEndPoint new_connection_ip_endpoint;
			if (listening_socket.Accept(new_connection_socket, &new_connection_ip_endpoint)) {
				Connection new_connection(new_connection_socket, new_connection_ip_endpoint);

				WSAPOLLFD new_connection_socket_fd = {};
				new_connection_socket_fd.fd = new_connection_socket.GetSocketHandle();
				new_connection_socket_fd.events = POLLRDNORM;
				new_connection_socket_fd.revents = 0;

				Accept(client_id++, new_connection, new_connection_socket_fd);
			}
		}
	}

	return true;
}

bool Server::Accept(uint32_t id, Connection connection, WSAPOLLFD master_fd) {
	if (!is_initialized) {
		printf("[bool Server::Accept(uint32_t, Connection, WSAPOLLFD)] - Function called without being initialized.\n");
		return false;
	}

	connections[id] = std::make_tuple(connection, master_fd, true);
	OnConnect(id);

	printf("[bool Server::Accept(uint32_t, Connection, WSAPOLLFD)] - Success.\n");
	return false;
}

bool Server::Disconnect(uint32_t connection_id) {
	if (!is_initialized) {
		printf("[Server::Disconnect(uint32_t)] - Function called while networks have not been initialized.\n");
		return false;
	}

	auto& disconnected_connection = std::get<0>(connections[connection_id]);
	disconnected_connection.Close();

	auto& client_is_connecting = std::get<2>(connections[connection_id]);
	client_is_connecting = false;

	OnDisconnect(connection_id);

	printf("[Server::Disconnect(uint32_t)] - Success.\n");
	return true;
}

bool Server::DisconnectAll() {
	if (!is_initialized) {
		printf("[Server::DisconnectAll()] - Function called while networks have not been initialized.\n");
		return false;
	}

	for (auto& connection : connections) {
		auto& disconnected_connection = std::get<0>(connection.second);
		disconnected_connection.Close();

		auto& client_is_connecting = std::get<2>(connection.second);
		client_is_connecting = false;

		OnDisconnect(connection.first);
	}

	printf("[Server::DisconnectAll()] - Success.\n");
	return true;
}

bool Server::CleanUpDisconnected() {
	if (!is_initialized) {
		printf("[Server::CleanUpDisconnected()] - Function called while networks have not been initialized.\n");
		return false;
	}

	for (auto it = connections.begin(); it != connections.end();) {
		auto& client_is_connecting = std::get<2>(it->second);
		if (!client_is_connecting) {
			it = connections.erase(it);
		}
		else {
			it++;
		}
	}
	return true;
}

bool Server::ProcessIncomming() {
	if (!is_initialized) {
		printf("[Server::ProcessConnection()] - Function called while networks have not been initialized.\n");
		return false;
	}

	for (auto& client : connections) {
		auto& client_connection = std::get<0>(client.second);
		PacketManager& incomming = client_connection.imcomming_packets;
		while (incomming.HasPending()) {
			std::shared_ptr<Packet> packet = incomming.Retrive();
			if (!ProcessPacket(packet)) {
				Disconnect(client.first);
				break;
			}
			incomming.Pop();
		}
	}
	return true;
}

bool Server::Send(uint32_t id, std::shared_ptr<Packet> packet) {
	if (!is_initialized) {
		printf("[Server::ProcessConnection()] - Function called while networks have not been initialized.\n");
		return false;
	}

	if (!std::get<2>(connections[id])) {
		printf("[Server::ProcessConnection()] - Function called while networks have not been initialized.\n");
		return false;
	}
	
	std::get<0>(connections[id]).outgoing_packets.Append(packet);
	return true;
}

bool Server::ProcessNetworks() {
	if (!is_initialized) {
		printf("[Server::ProcessConnection()] - Function called while networks have not been initialized.\n");
		return false;
	}

	for (auto& client : connections) {
		auto client_id = client.first;
		auto& client_connection = std::get<0>(client.second);
		auto& client_master_fd = std::get<1>(client.second);

		if (client_connection.outgoing_packets.HasPending()) {
			client_master_fd.events = POLLRDNORM | POLLWRNORM;
		}

		WSAPOLLFD client_temp_fd = client_master_fd;

		if (WSAPoll(&client_temp_fd, 1, 1) > 0) {

			// Error
			if (client_temp_fd.revents & POLLERR) {
				Disconnect(client_id);
				continue;
			}
			if (client_temp_fd.revents & POLLHUP) {
				Disconnect(client_id);
				continue;
			}
			if (client_temp_fd.revents & POLLNVAL) {
				Disconnect(client_id);
				continue;
			}

			// Read
			if (client_temp_fd.revents & POLLRDNORM) {
				PacketManager& incomming = client_connection.imcomming_packets;
				int received_bytes = 0;
				if (incomming.packet_process_task == PacketProcessTask::Header) {
					received_bytes = recv(
						client_temp_fd.fd,
						(char*)&incomming.packet_size + incomming.extraction_offset,
						sizeof(uint16_t) - incomming.extraction_offset,
						0
					);
				}
				else {
					received_bytes = recv(
						client_temp_fd.fd,
						(char*)&client_connection.buffer + incomming.extraction_offset,
						incomming.packet_size - incomming.extraction_offset,
						0
					);
				}

				if (received_bytes == 0) {
					Disconnect(client_id);
					continue;
				}

				if (received_bytes == SOCKET_ERROR) {
					int error = WSAGetLastError();
					if (error != WSAEWOULDBLOCK) {
						Disconnect(client_id);
						continue;
					}
				}

				if (received_bytes > 0) {
					incomming.extraction_offset += received_bytes;
					if (incomming.packet_process_task == PacketProcessTask::Header) {
						if (incomming.extraction_offset == sizeof(uint16_t)) {
							incomming.packet_size = ntohs(incomming.packet_size);
							if (incomming.packet_size > MAX_PACKET_SIZE) {
								Disconnect(client_id);
								continue;
							}
							incomming.extraction_offset = 0;
							incomming.packet_process_task = PacketProcessTask::Body;
						}
					}
					else {
						if (incomming.extraction_offset == incomming.packet_size) {
							std::shared_ptr<Packet> packet = std::make_shared<Packet>();
							packet->buffer.resize(incomming.packet_size);
							memcpy(&packet->buffer[0], client_connection.buffer, incomming.packet_size);

							incomming.Append(packet);

							incomming.packet_size = 0;
							incomming.extraction_offset = 0;
							incomming.packet_process_task = PacketProcessTask::Header;
						}
					}
				}
			}

			// Write
			if (client_temp_fd.revents & POLLWRNORM) {
				PacketManager& outgoing = client_connection.outgoing_packets;
				while (outgoing.HasPending()) {
					if (outgoing.packet_process_task == PacketProcessTask::Header) {
						outgoing.packet_size = outgoing.Retrive()->buffer.size();
						uint16_t packet_size = htons(outgoing.packet_size);
						int sent_bytes = send(
							client_temp_fd.fd,
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
							client_temp_fd.fd,
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
					client_master_fd.events = POLLRDNORM;
				}

			}

		}
	}
	return true;
}
