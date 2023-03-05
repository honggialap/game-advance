#pragma once
#ifndef __PONG_SCENE_H__
#define __PONG_SCENE_H__

#include "Common.h"
#include "GameObject.h"

// Forward declaration
class Game;
typedef Game* pGame;

class Scene {
protected:
	pGame game;
	std::unique_ptr<GameObject> gameObject;

	sf::View camera;

public:
	Scene(pGame game);
	~Scene();

public:
	sf::View& GetCamera();

	void Load(std::string data_path);
	void Unload();

	void Update(float elapsed);
	void Render(sf::RenderWindow& window);
};
typedef Scene* pScene;

#endif // !__PONG_SCENE_H__
