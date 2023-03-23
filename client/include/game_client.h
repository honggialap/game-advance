#pragma once
#ifndef __CLIENT_GAMECLIENT_H__
#define __CLIENT_GAMECLIENT_H__

#include "game.h"
#include "client.h"

namespace Client {

	class GameClient : public Engine::Game, public Engine::Client {
	protected:
		uint32_t id;

	protected:
		void Initialize(std::string data_path) override;
		void Shutdown() override;

	public:
		Engine::pScene CreateScene(unsigned int scene_type) override;

		void OnConnect() override;
		void OnDisconnect() override;
		void OnConnectFail() override;
		bool ProcessPacket(std::shared_ptr<Engine::Packet> packet) override;
	};
	typedef GameClient* pGameClient;

}

#endif // !__CLIENT_CLIENT_H__
