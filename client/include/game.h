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
	float update_elapsed_ms;
	float elapsed_ms_per_update;
	float render_elapsed_ms;
	float elapsed_ms_per_render;

	std::map<unsigned int, std::pair<unsigned int, std::string>> scene_list;
	unsigned int next_scene_id = -1;
	bool load_scene = false;
	std::unique_ptr<Scene> scene;

public:
	uint32_t player_id = 0;

	void Initialize(std::string data_path);
	void Shutdown();
	
	void Run(std::string data_path);

	void PlayScene(unsigned int scene_id);
	void LoadScene();
	pScene CreateScene(unsigned int scene_type);

	void OnConnect() override;
	void OnDisconnect() override;
	void OnConnectFail() override;
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;
};
typedef Game* pGame;

#endif // !__CLIENT_GAME_H__
