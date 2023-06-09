#include "engine/core/game.h"

namespace NSEngine {
	namespace NSCore {

		sf::RenderWindow& CGame::GetWindow() {
			return window;
		}

		void CGame::Initialize(std::string data_path) {
			std::ifstream data_file(data_path);
			nlohmann::json data = nlohmann::json::parse(data_file);

			auto& window_settings = data.at("window");
			std::string window_title = window_settings.at("title");
			unsigned int window_width = window_settings.at("width");
			unsigned int window_height = window_settings.at("height");
			float update_rate = window_settings.at("update_rate");
			float render_rate = window_settings.at("render_rate");

			window.create(
				sf::VideoMode(window_width, window_height),
				window_title,
				sf::Style::Titlebar | sf::Style::Close
			);
			window.setFramerateLimit(0);
			elapsed_ms_per_update = 1000.0f / update_rate;
			elapsed_ms_per_render = 1000.0f / render_rate;

			auto& scenes = data.at("scenes");
			for (auto& scene : scenes.at("scene_list")) {
				uint32_t id = scene.at("id");
				ESceneType type = ESceneType(scene.at("type"));
				std::string data_path = scene.at("data_path");
				scene_list[id] = std::make_pair(type, data_path);
			}
			PlayScene(scenes.at("start_scene_id"));
		}

		void CGame::Shutdown() {
			if (scene) scene->Unload();
		}

		void CGame::Exit() {
			window.close();
		}

		void CGame::PlayScene(uint32_t scene_id) {
			if (scene_list.find(scene_id) == scene_list.end()) {
				printf("Scene [%d] not found!\n", scene_id);
				return;
			}

			if (scene_id == next_scene_id) {
				printf("Scene [%d] is already playing or queuing for load!\n", scene_id);
				return;
			}

			load_scene = true;
			next_scene_id = scene_id;
		}

		void CGame::LoadScene() {
			load_scene = false;

			if (scene) scene->Unload();

			auto next_scene = scene_list.find(next_scene_id)->second;
			scene.reset(CreateScene(next_scene.first));

			scene->Load(next_scene.second);

			update_elapsed_ms = 0.0f;
			render_elapsed_ms = 0.0f;
		}

	}
}
