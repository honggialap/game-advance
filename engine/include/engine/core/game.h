#pragma once
#ifndef __ENGINE__CORE__GAME_H__
#define __ENGINE__CORE__GAME_H__

#include "engine/common.h"

#include "engine/core/scene.h"

namespace NSEngine {
	namespace NSCore {

		class CGame {
		protected:
			sf::RenderWindow window;

			b2Timer clock;
			float update_elapsed_ms;
			float elapsed_ms_per_update;
			float render_elapsed_ms;
			float elapsed_ms_per_render;

			typedef std::pair<ESceneType, std::string> SceneData;
			std::map<uint32_t, SceneData> scene_list;
			uint32_t next_scene_id = -1;
			bool load_scene = false;
			upScene scene;

		public:
			sf::RenderWindow& GetWindow();

			virtual void Initialize(std::string data_path);
			virtual void Shutdown();

			virtual void Run(std::string data_path) = 0;
			void Exit();

			void PlayScene(uint32_t scene_id);
			void LoadScene();

			virtual CScene* CreateScene(ESceneType scene_type) = 0;
		};
		typedef CGame* pGame;

	}
}

#endif // !__ENGINE__CORE__GAME_H__
