#pragma once
#ifndef __ENGINE__SCENE_H__
#define __ENGINE__SCENE_H__

#include "common.h"

// Forward declaration
class Game;
typedef Game* pGame;

class Scene {
protected:
	pGame game;

public:
	Scene(pGame game);
	virtual ~Scene() = 0;

	virtual void Load(std::string data_path) = 0;
	virtual void Unload() = 0;

	virtual void Update(float elapsed) = 0;
	virtual void Render(sf::RenderWindow& window) = 0;
};
typedef Scene* pScene;

#endif // !__ENGINE__SCENE_H__
