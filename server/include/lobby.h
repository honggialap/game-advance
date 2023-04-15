#pragma once
#ifndef __SERVER_LOBBY_H__
#define __SERVER_LOBBY_H__

#include "scene.h"
#include "game_object.h"

// Forward declaration
class Game;
typedef Game* pGame;

class Lobby : public Scene {
protected:
	enum State {
		Picking,
		Locked
	};
	State state = State::Picking;

	sf::Font font;
	sf::Text text;

	float count_down = 0;

public:
	Lobby(pGame game);
	~Lobby();

	void Load(std::string data_path) override;
	void Unload() override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	void OnConnect(uint32_t connection_id) override;
	void OnDisconnect(uint32_t connection_id) override;
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;

	void SendConfirmPacket();
	void SendNextScenePacket(uint32_t scene_id);

	void SetPlayerPick(uint32_t player_id, uint32_t client_id);
	void SetPlayerLock(uint32_t client_id);
};
typedef Lobby* pLobby;

#endif // !__SERVER_LOBBY_H__
