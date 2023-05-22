#pragma once
#ifndef __CLIENT__CLIENT_SCENE_H__
#define __CLIENT__CLIENT_SCENE_H__

#include "scene.h"
#include "packet.h"

class GameClient;

class ClientScene : public Scene {
protected:
	GameClient* game_client = nullptr;

public:
	ClientScene(Game* game);
	virtual ~ClientScene() = 0;

	virtual void OnConnect() = 0;
	virtual void OnDisconnect() = 0;
	virtual void OnConnectFail() = 0;
	virtual bool ProcessPacket(std::shared_ptr<Packet> packet) = 0;
};

#endif // !__CLIENT__CLIENT_SCENE_H__
