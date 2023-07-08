#pragma once
#ifndef __CLIENT__ACTOR__SHOVEL_H__
#define __CLIENT__ACTOR__SHOVEL_H__

#include "client/core/game_object.h"
#include "engine/actor/power_up/shovel.h"

namespace NSClient {
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

#endif // !__CLIENT__ACTOR__SHOVEL_H__
