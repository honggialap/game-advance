#pragma once
#ifndef __ENGINE_SAMPLELOBBYSCENE_H__
#define __ENGINE_SAMPLELOBBYSCENE_H__

#include "Scene.h"
#include "SampleGame.h"

class SampleLobbyScene : public Scene {
protected:
	pSampleGame sample_game;

public:
	SampleLobbyScene(pGame game);
	~SampleLobbyScene();

	void Load(std::string data_path) override;
	void Unload() override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	pGameObject CreateGameObject() override;
};
typedef SampleLobbyScene* pSampleLobbyScene;


#endif // !__ENGINE_SAMPLELOBBYSCENE_H__
