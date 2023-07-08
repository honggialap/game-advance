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
			NSClient::NSCore::pGame game_client;
			
			bool just_got_game_state = false;
			uint32_t tick_per_game_state = 8;
			uint32_t server_tick = 0;

		public:
			CWorld(NSEngine::NSCore::pGame game);
			~CWorld();

			void SetJustGotGameState(bool value);
			bool IsJustGotGameState();
			
			void SetServerTick(uint32_t value);
			uint32_t GetServerTick();

			void Load(nlohmann::json& data) override;
			void Unload() override;
		};
		typedef CWorld* pWorld;

	}
}

#endif // !__CLIENT__CORE__WORLD_H__
