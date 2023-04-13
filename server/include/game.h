#pragma once
#ifndef __SERVER_GAME_H__
#define __SERVER_GAME_H__

#include "common.h"
#include "server.h"
#include "scene.h"

#define SCENE_TYPE_LOBBY 1
#define SCENE_TYPE_WORLD 2

class Game : public Server {
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
	std::map<uint32_t, std::pair<uint32_t, bool>> players;

public:
	void Initialize(std::string data_path);
	void Shutdown();

	void Run(std::string data_path);

	void PlayScene(unsigned int scene_id);
	void LoadScene();
	pScene CreateScene(unsigned int scene_type);

	void OnConnect(uint32_t connection_id) override;
	void OnDisconnect(uint32_t connection_id) override;
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;
};
typedef Game* pGame;

#endif // !__SERVER_GAME_H__
