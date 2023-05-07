#pragma once
#ifndef __SERVER_SCENE_H__
#define __SERVER_SCENE_H__

#include "common.h"
#include "packet.h"

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

	virtual void OnConnect(uint32_t connection_id) = 0;
	virtual void OnDisconnect(uint32_t connection_id) = 0;
	virtual bool ProcessPacket(std::shared_ptr<Packet> packet) = 0;
};
typedef Scene* pScene;

#endif // !__SERVER_SCENE_H__
