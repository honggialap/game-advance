#pragma once
#ifndef __CLIENT_MAIN_SCENE_H__
#define __CLIENT_MAIN_SCENE_H__

#include "scene.h"
#include "world.h"

class MainScene : public Scene {
protected:
	enum State {
		Loading,
		Run
	};
	State state = Loading;

	sf::View camera;
	sf::Font font;
	sf::Text text;

	pWorld world = nullptr;

	bool ready_sent = false;
	bool ping_sent = false;
	uint32_t ping_tick = 0;

public:
	MainScene(pGame game) : Scene(game) {};
	~MainScene() {};

	void Load(std::string data_path) override;
	void Unload() override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	sf::View& GetCamera();

	void OnConnect() override;
	void OnDisconnect() override;
	void OnConnectFail() override;
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;

	void SendReadyPacket();
	void SendLoadPacket();
	void SendPingPacket();
};
typedef MainScene* pMainScene;

#endif // !__CLIENT_MAIN_SCENE_H__
