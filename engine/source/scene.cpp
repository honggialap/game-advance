#include "scene.h"

namespace Engine {
	
	Scene::Scene(pGame game)
		: game(game) {
	}

	Scene::~Scene() {
	}

	void Scene::Run(float tick_per_frame, sf::RenderWindow& window) {
		elapsedMs += clock.GetMilliseconds();
		clock.Reset();

		if (elapsedMs >= tick_per_frame) {
			Update(elapsedMs);

			window.clear(sf::Color::Black);
			Render(window);
			window.display();

			elapsedMs = 0.0f;
		}
		else {
			Sleep((DWORD)tick_per_frame - elapsedMs);
		}
	}

}