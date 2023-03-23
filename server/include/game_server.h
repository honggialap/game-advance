#pragma once
#ifndef __SERVER_GAMECSERVER_H__
#define __SERVER_GAMECSERVER_H__

#include "game.h"
#include "server.h"

namespace Server {

	class GameServer : public Engine::Game, public Engine::Server {
	public:
		Engine::pScene CreateScene(unsigned int scene_type) override;

		void OnConnect(Engine::Connection& connection) override;
		void OnDisconnect(Engine::Connection& connection) override;
		bool ProcessPacket(std::shared_ptr<Engine::Packet> packet) override;

	protected:
		void Initialize(std::string data_path) override;
		void Shutdown() override;
	};
	typedef GameServer* pGameServer;

}

#endif // !__SERVER_GAMECSERVER_H__
