#pragma once
#ifndef __ENGINE_SAMPLEGAMEOBJECT_H__
#define __ENGINE_SAMPLEGAMEOBJECT_H__

#include "GameObject.h"
#include "SampleWorldScene.h"

class SampleGameObject : public GameObject {
protected:
	pSampleGame sample_game;
	pSampleWorldScene sample_world_scene;

protected:
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Font font;
	sf::Text text;

	sf::SoundBuffer sfx_buffer;
	sf::Sound sfx;
	sf::Music music;

public:
	SampleGameObject(pGame game, pScene scene);
	~SampleGameObject();

public:
	void Load() override;
	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;
	void Unload() override;
};
typedef SampleGameObject* pSampleGameObject;

#endif // !__ENGINE_SAMPLEGAMEOBJECT_H__
