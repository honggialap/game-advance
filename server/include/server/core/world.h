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

			uint32_t rollback_tick = 0;
			bool rollback = false;

		public:
			CWorld(NSEngine::NSCore::pGame game);
			~CWorld();

			bool IsRollback();
			void SetRollback(bool value);

			uint32_t GetRollbackTick();
			void SetRollbackTick(uint32_t value);

			void Load(nlohmann::json& data);
			void Unload();
		};
		typedef CWorld* pWorld;

	}
}

#endif // !__SERVER__SERVER_WORLD_H__
