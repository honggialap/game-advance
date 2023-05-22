#pragma once
#ifndef __CLIENT_MAIN_SCENE_H__
#define __CLIENT_MAIN_SCENE_H__

#include "scene.h"
#include "client_scene.h"

#include "world.h"
#include "client_world.h"

class MainScene : public ClientScene {
protected:
	enum State {
		Loading,
		Run
	};
	State state = Loading;

	sf::View camera;
	sf::Font font;
	sf::Text text;

	ClientWorld* world = nullptr;

	bool ready_sent = false;
	bool ping_sent = false;
	uint32_t ping_tick = 0;

public:
	MainScene(pGame game);
	~MainScene();

	void Load(std::string data_path) final;
	void Unload() final;

	void Update(float elapsed) final;
	void Render(sf::RenderWindow& window) final;

	sf::View& GetCamera();

	void OnConnect() final;
	void OnDisconnect() final;
	void OnConnectFail() final;
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;

	void SendReadyPacket();
	void SendLoadPacket();
	void SendPingPacket();
};
typedef MainScene* pMainScene;

#endif // !__CLIENT_MAIN_SCENE_H__
