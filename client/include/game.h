#pragma once
#ifndef __ENGINE__GAME_H__
#define __ENGINE__GAME_H__

#include "common.h"
#include "scene.h"

class Game {
protected:
	sf::RenderWindow window;
	
	b2Timer clock;
	float update_elapsed_ms;
	float elapsed_ms_per_update;
	float render_elapsed_ms;
	float elapsed_ms_per_render;

	std::map<uint32_t, std::pair<uint32_t, std::string>> scene_list;
	uint32_t next_scene_id = -1;
	bool load_scene = false;
	std::unique_ptr<Scene> scene;

public:
	sf::RenderWindow& GetWindow() { return window; }

	virtual void Initialize(std::string data_path);
	virtual void Shutdown();
	
	virtual void Run(std::string data_path) = 0;
	void Exit() { window.close(); }

	void PlayScene(uint32_t scene_id);
	void LoadScene();
	virtual pScene CreateScene(uint32_t scene_type) = 0;
};
typedef Game* pGame;

#endif // !__ENGINE__GAME_H__
