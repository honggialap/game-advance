#pragma once
#ifndef __ENGINE_GAMEOBJECT_H__
#define __ENGINE_GAMEOBJECT_H__

#include "common.h"

namespace Engine {

	// Forward declaration
	class Game;
	typedef Game* pGame;
	class Scene;
	typedef Scene* pScene;

	class GameObject : public sf::Transformable {
	protected:
		pGame game;
		pScene scene;

		uint32_t networks_id;

	public:
		GameObject(pGame game, pScene scene);
		~GameObject();

	public:
		virtual void Load(std::string data_path) = 0;
		virtual void Unload() = 0;

		virtual void Update(float elapsed) = 0;
		virtual void Render(sf::RenderWindow& window) = 0;

		virtual void OnCollisionEnter(GameObject* other) = 0;
		virtual void OnCollisionExit(GameObject* other) = 0;
	};
	typedef GameObject* pGameObject;

}

#endif // !__ENGINE_GAMEOBJECT_H__
