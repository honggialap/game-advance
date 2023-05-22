#pragma once
#ifndef __CLIENT_GAME_CLIENT_H__
#define __CLIENT_GAME_CLIENT_H__

#include "common.h"
#include "client.h"
#include "game.h"
#include "client_scene.h"

#define SCENE_LOBBY		uint32_t	(	1001	)
#define SCENE_MAIN		uint32_t	(	1002	)

class GameClient : public Game, public Client {
protected:
	ClientScene* client_scene;
	uint32_t player_id = 0;

public:
	void SetPlayerId(uint32_t value) { player_id = value; }
	uint32_t GetPlayerId() { return player_id; }

	void Initialize(std::string data_path) final;
	void Shutdown() final;

	void Run(std::string data_path) final;

	pScene CreateScene(uint32_t scene_type) final;

	void OnConnect() final;
	void OnDisconnect() final;
	void OnConnectFail() final;
	bool ProcessPacket(std::shared_ptr<Packet> packet) final;
};

#endif // !__CLIENT_GAME_CLIENT_H__
