#pragma once
#ifndef __ENGINE_GAME_H__
#define __ENGINE_GAME_H__

#include "common.h"
#include "scene.h"

namespace Engine {

	class Game {
	protected:
		sf::RenderWindow window;
		float tick_per_frame;

		std::map<unsigned int, std::pair<unsigned int, std::string>> scene_list;
		unsigned int next_scene_id = -1;
		bool load_scene = false;
		std::unique_ptr<Scene> scene;

	public:
		void Run(std::string data_path);
		void PlayScene(unsigned int scene_id);
		virtual pScene CreateScene(unsigned int scene_type) = 0;

	protected:
		virtual void Initialize(std::string data_path);
		virtual void Shutdown();

		virtual void Update(float elapsedMs);
		virtual void Render(sf::RenderWindow& window);

		void LoadScene();
	};
	typedef Game* pGame;

}

#endif // !__ENGINE_GAME_H__
