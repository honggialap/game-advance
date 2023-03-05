#pragma once
#ifndef __ENGINE_SCENE_H__
#define __ENGINE_SCENE_H__

#include "Common.h"
#include "GameObject.h"

class Game;
typedef Game* pGame;

class Scene {
protected:
	pGame game;

public:
	Scene(pGame game);
	~Scene();

public:
	virtual void Load(std::string data_path) = 0;
	virtual void Unload() = 0;

	virtual void Update(float elapsed) = 0;
	virtual void Render(sf::RenderWindow& window) = 0;

	virtual pGameObject CreateGameObject() = 0;
};
typedef Scene* pScene;

#endif // !__ENGINE_SCENE_H__
