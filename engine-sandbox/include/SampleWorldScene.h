#pragma once
#ifndef __ENGINE_SAMPLEWORLDSCENE_H__
#define __ENGINE_SAMPLEWORLDSCENE_H__

#include "Scene.h"
#include "SampleGame.h"

class SampleWorldScene : public Scene {
protected:
	pSampleGame sample_game;

protected:
	sf::View camera;
	std::unique_ptr<GameObject> game_object;

public:
	sf::View& GetCamera();

public:
	SampleWorldScene(pGame game);
	~SampleWorldScene();

public:
	void Load(std::string data_path) override;
	void Unload() override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	pGameObject CreateGameObject() override;
};
typedef SampleWorldScene* pSampleWorldScene;


#endif // !__ENGINE_SAMPLEWORLDSCENE_H__
