#include "server.h"

namespace Engine {

	bool Server::Listen(IPEndPoint ip_endpoint) {
		connections.clear();
		master_fd.clear();
		is_running = false;

		int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
		if (result != 0) {
			return false;
		}

		if (LOBYTE(wsa_data.wVersion) != 2 || HIBYTE(wsa_data.wVersion) != 2) {
			return false;
		}

		listening_socket = Socket(IPVersion::IPv6);
		if (!listening_socket.Create()) {
			return false;
		}

		if (!listening_socket.SetSocketBlocking(false)) {
			return false;
		}

		if (!listening_socket.Listen(IPEndPoint("::1", 27015))) {
			listening_socket.Close();
			return false;
		}

		WSAPOLLFD listening_socket_fd = {};
		listening_socket_fd.fd = listening_socket.GetSocketHandle();
		listening_socket_fd.events = POLLRDNORM | POLLWRNORM;
		listening_socket_fd.revents = 0;

		master_fd.push_back(listening_socket_fd);

		is_running = true;
		return true;
	}

	void Server::CleanUp() {
		WSACleanup();
	}

	void Server::ProcessNetworks() {

		for (int i = 0; i < connections.size(); i++) {
			if (connections[i].outgoing_packets.HasPending()) {
				master_fd[i + 1].events = POLLRDNORM | POLLWRNORM;
			}
		}

		temp_fd = master_fd;

		if (WSAPoll(temp_fd.data(), temp_fd.size(), 1) > 0) {

			// Listener
			WSAPOLLFD& listening_socket_fd = temp_fd[0];
			if (listening_socket_fd.revents & POLLRDNORM) {
				Socket new_connection_socket;
				IPEndPoint new_connection_ip_endpoint;
				if (listening_socket.Accept(new_connection_socket, &new_connection_ip_endpoint)) {
					Connection new_connection(new_connection_socket, new_connection_ip_endpoint);
					
					WSAPOLLFD new_connection_socket_fd = {};
					new_connection_socket_fd.fd = new_connection_socket.GetSocketHandle();
					new_connection_socket_fd.events = POLLRDNORM;
					new_connection_socket_fd.revents = 0;

					connections.push_back(new_connection);
					master_fd.push_back(new_connection_socket_fd);

					OnConnect(new_connection);
				}
			}
			// End of Listeners

			// Connections
			for (int i = temp_fd.size() - 1; i >= 1; i--) {
				int connection_index = i - 1;

				// Error
				Connection& connection = connections[connection_index];
				if (temp_fd[i].revents & POLLERR) {
					CloseConnection(connection_index);
					continue;
				}
				if (temp_fd[i].revents & POLLHUP) {
					CloseConnection(connection_index);
					continue;
				}
				if (temp_fd[i].revents & POLLNVAL) {
					CloseConnection(connection_index);
					continue;
				}
				// End of Error

				// Read
				if (temp_fd[i].revents & POLLRDNORM) {
					PacketManager& incomming = connection.imcomming_packets;
					int received_bytes = 0;
					if (incomming.packet_process_task == PacketProcessTask::Header) {
						received_bytes = recv(
							temp_fd[i].fd, 
							(char*)&incomming.packet_size + incomming.extraction_offset,
							sizeof(uint16_t) - incomming.extraction_offset,
							0
						);
					}
					else {
						received_bytes = recv(
							temp_fd[i].fd,
							(char*)&connection.buffer + incomming.extraction_offset,
							incomming.packet_size - incomming.extraction_offset,
							0
						);
					}

					if (received_bytes == 0) {
						CloseConnection(connection_index);
						continue;
					}

					if (received_bytes == SOCKET_ERROR) {
						int error = WSAGetLastError();
						if (error != WSAEWOULDBLOCK) {
							CloseConnection(connection_index);
							continue;
						}
					}

					if (received_bytes > 0) {
						incomming.extraction_offset += received_bytes;
						if (incomming.packet_process_task == PacketProcessTask::Header) {
							if (incomming.extraction_offset == sizeof(uint16_t)) {
								incomming.packet_size = ntohs(incomming.packet_size);
								if (incomming.packet_size > MAX_PACKET_SIZE) {
									CloseConnection(connection_index);
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
				if (temp_fd[i].revents & POLLWRNORM) {
					PacketManager& outgoing = connection.outgoing_packets;
					while (outgoing.HasPending()) {
						if (outgoing.packet_process_task == PacketProcessTask::Header) {
							outgoing.packet_size = outgoing.Retrive()->buffer.size();
							uint16_t packet_size = htons(outgoing.packet_size);
							int sent_bytes = send(
								temp_fd[i].fd,
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
								temp_fd[i].fd,
								(char*)(buffer) + outgoing.extraction_offset,
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
						master_fd[i].events = POLLRDNORM;
					}

				}
				// End of Write
			}
			// End of Connections

		}

		for (int i = connections.size() - 1; i >= 0; i--) {
			PacketManager& incomming = connections[i].imcomming_packets;
			while (incomming.HasPending()) {
				std::shared_ptr<Packet> packet = incomming.Retrive();
				if (!ProcessPacket(packet)) {
					CloseConnection(i);
					break;
				}
				incomming.Pop();
			}
		}

	}

	void Server::CloseConnection(int connection_index) {
		Connection& connection = connections[connection_index];
		OnDisconnect(connection);
		master_fd.erase(master_fd.begin() + (connection_index + 1));
		temp_fd.erase(master_fd.begin() + (connection_index + 1));
		connection.Close();
		connections.erase(connections.begin() + connection_index);
	}

	bool Server::ProcessPacket(std::shared_ptr<Packet> packet) {
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