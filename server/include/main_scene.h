#pragma once
#ifndef __SERVER_MAIN_SCENE_H__
#define __SERVER_MAIN_SCENE_H__

#include "scene.h"
#include "world.h"

#include "tank.h"
#include "bullet.h"
#include "wall.h"

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

	uint32_t ready_client_count = 0;
	uint32_t load_client_count = 0;

public:

	pWorld world = nullptr;

	std::map<uint32_t, uint32_t> player_ping;

	MainScene(pGame game) : Scene(game) {};
	~MainScene() {};

	void Load(std::string data_path) override;
	void Unload() override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	sf::View& GetCamera();

	void OnConnect(uint32_t connection_id) override;
	void OnDisconnect(uint32_t connection_id) override;
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;

	void SendLoadPacket();
	void SendStartGamePacket();
	void SendReplyPingPacket(uint32_t client_id, uint32_t reply_ping_tick);

	void SendGameStatePacket();

	void RelayMovePacket(uint32_t client_id, uint32_t tick, MoveCommand move_command);
};
typedef MainScene* pMainScene;

#endif // !__SERVER_MAIN_SCENE_H__
