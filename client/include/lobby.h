#pragma once
#ifndef __CLIENT_LOBBY_H__
#define __CLIENT_LOBBY_H__

#include "scene.h"
#include "game_object.h"

// Forward declaration
class Game;
typedef Game* pGame;

class Lobby : public Scene {
	enum State {
		Picking,
		Locked
	};
	State state;

protected:
	sf::Font font;
	sf::Text text;

	bool picked;
	bool locked;

public:
	Lobby(pGame game);
	~Lobby();

	void Load(std::string data_path) override;
	void Unload() override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	void OnConnect() override;
	void OnDisconnect() override;
	void OnConnectFail() override;
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;
};
typedef Lobby* pLobby;

#endif // !__CLIENT_LOBBY_H__
