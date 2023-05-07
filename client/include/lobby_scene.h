#pragma once
#ifndef __CLIENT_LOBBY_SCENE_H__
#define __CLIENT_LOBBY_SCENE_H__

#include "scene.h"

class LobbyScene : public Scene {
protected:
	enum State {
		Picking,
		Locked
	};
	State state = State::Picking;

	sf::Font font;
	sf::Text text;

	bool pick_sent = false;
	bool lockable = false;

public:
	LobbyScene(pGame game) : Scene(game) {};
	~LobbyScene() {};

	void Load(std::string data_path) override;
	void Unload() override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	void OnConnect() override;
	void OnDisconnect() override;
	void OnConnectFail() override;
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;

	void SendPickPacket(uint32_t player_id_value);
	void SendLockPacket();
};
typedef LobbyScene* pLobbyScene;

#endif // !__CLIENT_LOBBY_SCENE_H__
