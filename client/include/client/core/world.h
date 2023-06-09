#pragma once
#ifndef __CLIENT__CORE__WORLD_H__
#define __CLIENT__CORE__WORLD_H__

#include "engine/core/world.h"

#include "client/core/game.h"

namespace NSClient {
	namespace NSCore {

		class CWorld
			: public NSEngine::NSCore::CWorld {
		protected:
			CGame* game_client;

		public:
			CWorld(NSEngine::NSCore::pGame game);
			~CWorld();
		};
		typedef CWorld* pWorld;

	}
}

#endif // !__CLIENT__CORE__WORLD_H__
