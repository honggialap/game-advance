#pragma once
#ifndef __CLIENT_GAMECLIENT_H__
#define __CLIENT_GAMECLIENT_H__

#include "common.h"
#include "client.h"

namespace Client {

	class GameClient : public Engine::Client {
	public:
		uint32_t id;

		float tick_count;
		float total_elapsed_ms;

		sf::RenderWindow window;
		float tick_per_frame;
		float elapsed_ms;
		b2Timer clock;

		enum State {
			Connecting,
			Waiting,
		};
		State state;

		void Initialize();
		void Shutdown();

		void Run();

		void Update(float elapsed_ms);
		void Render(sf::RenderWindow& window);

		void OnConnect() override;
		void OnDisconnect() override;
		void OnConnectFail() override;
		bool ProcessPacket(std::shared_ptr<Engine::Packet> packet) override;
	};
	typedef GameClient* pGameClient;

}

#endif // !__CLIENT_CLIENT_H__
