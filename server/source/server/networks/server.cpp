#include "server/networks/server.h"

namespace NSServer {
	namespace NSNetworks {

		void CServer::SetHostAddress(NSEngine::NSNetworks::CIPEndPoint value) {
			host_address = value;
		}

		NSEngine::NSNetworks::CIPEndPoint CServer::GetHostAddress() {
			return host_address;
		}

		void CServer::SetMaxConnectionLimit(uint32_t value) {
			max_connection_count = value;
		}

		uint32_t CServer::GetMaxConnectionLimit() {
			return max_connection_count;
		}

		bool CServer::Initialize() {
			if (is_initialized) {
				printf("[bool Server::Initialize(IPEndPoint,uint32t)] - Already initialized.\n");
				return false;
			}

			if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
				printf("[bool Server::Initialize(IPEndPoint,uint32t)] - WSAStartup failed with error code: %d.\n", WSAGetLastError());
				return false;
			}

			is_initialized = true;

			printf("[bool Server::Initialize(IPEndPoint,uint32t)] - Success.\n");
			return true;
		}

		bool CServer::Shutdown() {
			if (!is_initialized) {
				printf("[bool Server::Shutdown()] - Not initialized yet.\n");
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

		bool CServer::StartListen() {
			if (!is_initialized) {
				printf("[bool Server::StartListen()] - Not initialized yet.\n");
				return false;
			}

			if (is_listening) {
				printf("[bool Server::StartListen()] - Already listening.\n");
				return false;
			}

			listening_socket = NSEngine::NSNetworks::CSocket(host_address.GetIPVersion());
			if (!listening_socket.Create()) {
				printf("[bool Server::StartListen()] - Failed to create listening socket.\n");
				return false;
			}

			if (!listening_socket.SetSocketBlocking(false)) {
				listening_socket.Close();

				printf("[bool Server::StartListen()] - Failed to set listening socket blocking.\n");
				return false;
			}

			if (!listening_socket.Listen(host_address)) {
				listening_socket.Close();

				printf("[bool Server::StartListen()] - Failed to listen for connection.\n");
				return false;
			}

			listening_master_fd = {};
			listening_master_fd.fd = listening_socket.GetSocketHandle();
			listening_master_fd.events = POLLRDNORM;
			listening_master_fd.revents = 0;

			is_listening = true;

			printf("[bool Server::StartListen()] - Success.\n");
			return true;
		}

		bool CServer::StopListen() {
			if (!is_initialized) {
				printf("[bool Server::StopListen()] - Not initialized yet.\n");
				return false;
			}

			if (!is_listening) {
				printf("[bool Server::StopListen()] - Not listening yet.\n");
				return false;
			}

			listening_socket.Close();
			listening_master_fd = {};

			is_listening = false;

			printf("[bool Server::StopListen()] - Sucess.\n");
			return true;
		}

		bool CServer::Accept(uint32_t id, NSEngine::NSNetworks::CConnection connection, WSAPOLLFD master_fd) {
			if (!is_initialized) {
				printf("[bool Server::Accept(uint32_t,Connection,WSAPOLLFD)] - Not initialized yet.\n");
				return false;
			}

			connections[id] = std::make_tuple(connection, master_fd, true);
			OnConnect(id);

			printf("[bool Server::Accept(uint32_t,Connection,WSAPOLLFD)] - Success.\n");
			return false;
		}

		bool CServer::Disconnect(uint32_t connection_id) {
			if (!is_initialized) {
				printf("[bool Server::Disconnect(uint32_t)] - Not initialized yet.\n");
				return false;
			}

			auto& disconnected_connection = std::get<0>(connections.at(connection_id));
			disconnected_connection.Close();

			auto& client_is_connecting = std::get<2>(connections.at(connection_id));
			client_is_connecting = false;

			OnDisconnect(connection_id);

			printf("[bool Server::Disconnect(uint32_t)] - Success.\n");
			return true;
		}

		bool CServer::ProcessNetworks() {
			if (!is_initialized) {
				printf("[bool Server::ProcessNetworks()] - Not initialized yet.\n");
				return false;
			}

			if (is_listening) {
				WSAPOLLFD listening_temp_fd = listening_master_fd;
				if (WSAPoll(&listening_temp_fd, 1, 1) > 0) {
					if (listening_temp_fd.revents & POLLRDNORM) {
						NSEngine::NSNetworks::CSocket new_connection_socket;
						NSEngine::NSNetworks::CIPEndPoint new_connection_ip_endpoint;
						if (listening_socket.Accept(new_connection_socket, &new_connection_ip_endpoint)) {
							NSEngine::NSNetworks::CConnection new_connection(new_connection_socket, new_connection_ip_endpoint);

							WSAPOLLFD new_connection_socket_fd = {};
							new_connection_socket_fd.fd = new_connection_socket.GetSocketHandle();
							new_connection_socket_fd.events = POLLRDNORM;
							new_connection_socket_fd.revents = 0;

							Accept(client_id++, new_connection, new_connection_socket_fd);
						}
					}
				}
			}

			// Connections
			std::vector<std::thread> connection_threads;
			for (auto& client : connections) {
				auto client_id = client.first;
				auto& client_connection = std::get<0>(client.second);
				auto& client_master_fd = std::get<1>(client.second);

				connection_threads.emplace_back(
					[&]() {
						if (client_connection.outgoing_packets.HasPending()) {
							client_master_fd.events = POLLRDNORM | POLLWRNORM;
						}

						WSAPOLLFD client_temp_fd = client_master_fd;

						if (WSAPoll(&client_temp_fd, 1, 1) > 0) {

							// Error
							if (client_temp_fd.revents & POLLERR) {
								Disconnect(client_id);
								return;
							}
							if (client_temp_fd.revents & POLLHUP) {
								Disconnect(client_id);
								return;
							}
							if (client_temp_fd.revents & POLLNVAL) {
								Disconnect(client_id);
								return;
							}

							// Read
							if (client_temp_fd.revents & POLLRDNORM) {
								NSEngine::NSNetworks::CPacketManager& incomming = client_connection.imcomming_packets;
								int received_bytes = 0;
								if (incomming.packet_process_task == NSEngine::NSNetworks::EPacketProcessTask::Header) {
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
									return;
								}

								if (received_bytes == SOCKET_ERROR) {
									int error = WSAGetLastError();
									if (error != WSAEWOULDBLOCK) {
										Disconnect(client_id);
										return;
									}
								}

								if (received_bytes > 0) {
									incomming.extraction_offset += received_bytes;
									if (incomming.packet_process_task == NSEngine::NSNetworks::EPacketProcessTask::Header) {
										if (incomming.extraction_offset == sizeof(uint16_t)) {
											incomming.packet_size = ntohs(incomming.packet_size);
											if (incomming.packet_size > MAX_PACKET_SIZE) {
												Disconnect(client_id);
												return;
											}
											incomming.extraction_offset = 0;
											incomming.packet_process_task = NSEngine::NSNetworks::EPacketProcessTask::Body;
										}
									}
									else {
										if (incomming.extraction_offset == incomming.packet_size) {
											std::shared_ptr<NSEngine::NSNetworks::CPacket> packet = std::make_shared<NSEngine::NSNetworks::CPacket>();
											packet->buffer.resize(incomming.packet_size);
											memcpy(&packet->buffer[0], client_connection.buffer, incomming.packet_size);

											mutex.lock();
											incomming.Append(packet);
											mutex.unlock();

											incomming.packet_size = 0;
											incomming.extraction_offset = 0;
											incomming.packet_process_task = NSEngine::NSNetworks::EPacketProcessTask::Header;
										}
									}
								}
							}

							// Write
							if (client_temp_fd.revents & POLLWRNORM) {
								NSEngine::NSNetworks::CPacketManager& outgoing = client_connection.outgoing_packets;
								while (outgoing.HasPending()) {
									if (outgoing.packet_process_task == NSEngine::NSNetworks::EPacketProcessTask::Header) {
										mutex.lock();
										outgoing.packet_size = outgoing.Retrive()->buffer.size();
										mutex.unlock();

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
											outgoing.packet_process_task = NSEngine::NSNetworks::EPacketProcessTask::Body;
										}
										else {
											break;
										}
									}
									else {
										mutex.lock();
										char* buffer = &outgoing.Retrive()->buffer[0];
										mutex.unlock();

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
											outgoing.packet_process_task = NSEngine::NSNetworks::EPacketProcessTask::Header;

											mutex.lock();
											outgoing.Pop();
											mutex.unlock();
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
				);
			}
			for (auto& thread : connection_threads) {
				thread.join();
			}

			// Clean up disconnected
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

		bool CServer::ProcessPackets() {
			for (auto& client : connections) {
				auto& client_connection = std::get<0>(client.second);
				NSEngine::NSNetworks::CPacketManager& incomming = client_connection.imcomming_packets;
				while (incomming.HasPending()) {
					mutex.lock();
					std::shared_ptr<NSEngine::NSNetworks::CPacket> packet = incomming.Retrive();
					mutex.unlock();

					if (!ProcessPacket(packet)) {
						Disconnect(client.first);
						break;
					}

					mutex.lock();
					incomming.Pop();
					mutex.unlock();
				}
			}
			return true;
		}

		bool CServer::Send(uint32_t id, std::shared_ptr<NSEngine::NSNetworks::CPacket> packet) {
			if (!is_initialized) {
				printf("[bool Server::Send(uint32_t, std::shared_ptr<Packet>)] - Not initialized yet.\n");
				return false;
			}

			if (!std::get<2>(connections.at(id))) {
				printf("[bool Server::Send(uint32_t, std::shared_ptr<Packet>)] - Connection already disconnected.\n");
				return false;
			}

			mutex.lock();
			std::get<0>(connections.at(id)).outgoing_packets.Append(packet);
			mutex.unlock();

			return true;
		}

		bool CServer::SendAll(std::shared_ptr<NSEngine::NSNetworks::CPacket> packet) {
			if (!is_initialized) {
				printf("[bool Server::SendAll(std::shared_ptr<Packet>)] - Not initialized yet.\n");
				return false;
			}

			for (auto& client : connections) {
				if (std::get<2>(client.second)) {
					mutex.lock();
					std::get<0>(client.second).outgoing_packets.Append(packet);
					mutex.unlock();
				}
			}

			return true;
		}

		bool CServer::SendAllExcept(uint32_t id, std::shared_ptr<NSEngine::NSNetworks::CPacket> packet) {
			if (!is_initialized) {
				printf("[bool Server::SendAllExcept(uint32_t,std::shared_ptr<Packet>)] - Not initialized yet.\n");
				return false;
			}

			for (auto& client : connections) {
				if (std::get<2>(client.second) && client.first != id) {
					mutex.lock();
					std::get<0>(client.second).outgoing_packets.Append(packet);
					mutex.unlock();
				}
			}

			return true;
		}

	}
}
