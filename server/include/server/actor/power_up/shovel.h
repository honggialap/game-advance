#pragma once
#ifndef __SERVER__ACTOR__SHOVEL_H__
#define __SERVER__ACTOR__SHOVEL_H__

#include "server/core/game_object.h"
#include "engine/actor/power_up/shovel.h"

namespace NSServer {
	namespace NSActor {

		class CShovel
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CShovel
		{
		public:
			static CShovel* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, nlohmann::json& components_data
			);

			CShovel(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CShovel();

		};
		typedef CShovel* pShovel;

	}
}

#endif // !__SERVER__ACTOR__SHOVEL_H__
