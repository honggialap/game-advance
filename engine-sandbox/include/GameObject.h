#pragma once
#ifndef __PONG_GAMEOBJECT_H__
#define __PONG_GAMEOBJECT_H__

#include "Common.h"

class Game;
typedef Game* pGame;

class Scene;
typedef Scene* pScene;

class GameObject : public sf::Transformable {
protected:
	Game* game;
	Scene* scene;

protected:
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Font font;
	sf::Text text;

	sf::SoundBuffer sfx_buffer;
	sf::Sound sfx;
	sf::Music music;

public:
	GameObject(Game* pGame, Scene* pScene);
	~GameObject();

public:
	void Load();

	void Update(float elapsed);
	
	void Render(sf::RenderWindow& window);

	void Unload();
};



#endif // !__PONG_GAMEOBJECT_H__
