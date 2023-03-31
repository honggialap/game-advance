#pragma once
#ifndef __CLIENT_SCENE_H__
#define __CLIENT_SCENE_H__

#include "common.h"
#include "packet.h"
#include "game_object.h"

// Forward declaration
class Game;
typedef Game* pGame;

class Scene {
protected:
	pGame game;

public:
	Scene(pGame game) : game(game) {};

	virtual void Load(std::string data_path) = 0;
	virtual void Unload() = 0;

	virtual void Update(float elapsed) = 0;
	virtual void Render(sf::RenderWindow& window) = 0;
	
	virtual void OnConnect() = 0;
	virtual void OnDisconnect() = 0;
	virtual void OnConnectFail() = 0;
	virtual bool ProcessPacket(std::shared_ptr<Packet> packet) = 0;
};
typedef Scene* pScene;

#endif // !__CLIENT_SCENE_H__
