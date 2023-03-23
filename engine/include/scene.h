#pragma once
#ifndef __ENGINE_SCENE_H__
#define __ENGINE_SCENE_H__

#include "common.h"
#include "game_object.h"

namespace Engine {

	// Forward declaration
	class Game;
	typedef Game* pGame;

	class Scene {
	protected:
		pGame game; 

		float elapsedMs = 0.0f;
		b2Timer clock;

	public:
		Scene(pGame game);
		~Scene();

		virtual void Run(float tick_per_frame, sf::RenderWindow& window);

		virtual void Load(std::string data_path) = 0;
		virtual void Unload() = 0;

		virtual void Update(float elapsed) = 0;
		virtual void Render(sf::RenderWindow& window) = 0;

		virtual pGameObject CreateGameObject(unsigned int game_object_type) = 0;
	};
	typedef Scene* pScene;

}

#endif // !__ENGINE_SCENE_H__
