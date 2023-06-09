#pragma once
#ifndef __SERVER__CORE__WORLD_H__
#define __SERVER__CORE__WORLD_H__

#include "engine/core/world.h"

#include "server/core/game.h"

namespace NSServer {
	namespace NSCore {

		class CWorld
			: public NSEngine::NSCore::CWorld {
		protected:
			pGame game_server;

		public:
			CWorld(NSEngine::NSCore::pGame game);
			~CWorld();
		};
		typedef CWorld* pWorld;

	}
}

#endif // !__SERVER__SERVER_WORLD_H__
