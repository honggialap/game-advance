#pragma once
#ifndef __ENGINE_SAMPLEGAME_H__
#define __ENGINE_SAMPLEGAME_H__

#include "Game.h"

#define SCENE_ID_LOBBY 0
#define SCENE_ID_WORLD 1

class SampleGame : public Game {
public:
	virtual pScene CreateScene(unsigned int scene_type) override;

protected:
	void Initialize(std::string data_path) override;
	void Shutdown() override;
};
typedef SampleGame* pSampleGame;

#endif // !__ENGINE_SAMPLEGAME_H__
