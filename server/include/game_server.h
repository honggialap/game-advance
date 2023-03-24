#pragma once
#ifndef __SERVER_GAMECSERVER_H__
#define __SERVER_GAMECSERVER_H__

#include "common.h"
#include "server.h"

namespace Server {

	class GameServer : public Engine::Server {
	public:
		sf::RenderWindow window;
		float tick_per_frame;
		float elapsed_ms;
		b2Timer clock;

		void Initialize();
		void Shutdown();

		void Run();

		void Update(float elapsed_ms);
		void Render(sf::RenderWindow& window);

		void OnConnect(uint32_t connection_id) override;
		void OnDisconnect(uint32_t connection_id) override;
		bool ProcessPacket(std::shared_ptr<Engine::Packet> packet) override;

	};
	typedef GameServer* pGameServer;

}

#endif // !__SERVER_GAMECSERVER_H__
