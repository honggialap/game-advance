#pragma once
#ifndef __ENGINE__CORE__SCENE_H__
#define __ENGINE__CORE__SCENE_H__

#include "engine/common.h"
#include "engine/shared.h"

namespace NSEngine {
	namespace NSCore {

		class CGame;
		typedef CGame* pGame;

		class CScene {
		protected:
			pGame game;

		public:
			CScene(pGame game);
			virtual ~CScene() = 0;

			virtual void Load(std::string data_path) = 0;
			virtual void Unload() = 0;

			virtual void Update(float elapsed) = 0;
			virtual void Render(sf::RenderWindow& window) = 0;
		};
		typedef CScene* pScene;
		typedef std::unique_ptr<CScene> upScene;

	}
}

#endif // !__ENGINE__CORE__SCENE_H__
