#pragma once
#ifndef __ENGINE_GAMEOBJECT_H__
#define __ENGINE_GAMEOBJECT_H__

#include "Common.h"

class Game;
typedef Game* pGame;

class Scene;
typedef Scene* pScene;

class GameObject : public sf::Transformable {
protected:
	Game* game;
	Scene* scene;

public:
	GameObject(Game* pGame, Scene* pScene);
	~GameObject();

public:
	virtual void Load() = 0;
	virtual void Update(float elapsed) = 0;
	virtual void Render(sf::RenderWindow& window) = 0;
	virtual void Unload() = 0;
};
typedef GameObject* pGameObject;


#endif // !__ENGINE_GAMEOBJECT_H__
