#pragma once
#ifndef __CLIENT_GAMECSERVER_H__
#define __CLIENT_GAMECSERVER_H__

#include "game.h"

namespace Server {

	class GameServer : public Engine::Game {
	protected:
		void Initialize() override;
		void Shutdown() override;

		void Update() override;
		void Render() override;

		void CreateScene() override;
	};

}

#endif // !__CLIENT_GAMECSERVER_H__
