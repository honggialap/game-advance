#pragma once
#ifndef __SERVER_LOBBY_H__
#define __SERVER_LOBBY_H__

#include "scene.h"
#include "game_object.h"

// Forward declaration
class Game;
typedef Game* pGame;

class Lobby : public Scene {
public:
	Lobby(pGame game) : Scene(game) {};

	void Load(std::string data_path) override;
	void Unload() override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	void OnConnect(uint32_t connection_id) override;
	void OnDisconnect(uint32_t connection_id) override;
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;
};
typedef Lobby* pLobby;

#endif // !__SERVER_LOBBY_H__
