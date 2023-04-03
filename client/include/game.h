#pragma once
#ifndef __CLIENT_GAME_H__
#define __CLIENT_GAME_H__

#include "common.h"
#include "client.h"
#include "scene.h"

#define SCENE_TYPE_LOBBY 1
#define SCENE_TYPE_WORLD 2

class Game : public Client {
protected:
	sf::RenderWindow window;
	b2Timer clock;
	float elapsed_ms_per_tick;
	float elapsed_ms;
	float total_elapsed_ms;
	uint32_t tick_per_ping;
	uint32_t tick_per_ping_count;
	uint32_t tick_count;
	float ping;

	std::map<unsigned int, std::pair<unsigned int, std::string>> scene_list;
	unsigned int next_scene_id = -1;
	bool load_scene = false;
	std::unique_ptr<Scene> scene;

public:
	void Initialize(std::string data_path);
	void Shutdown();
	
	void Run(std::string data_path);

	void PlayScene(unsigned int scene_id);
	void LoadScene();
	pScene CreateScene(unsigned int scene_type);

	float GetPing() { return ping; }

	void OnConnect() override;
	void OnDisconnect() override;
	void OnConnectFail() override;
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;
};
typedef Game* pGame;

#endif // !__CLIENT_GAME_H__
