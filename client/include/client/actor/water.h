#pragma once
#ifndef __CLIENT__ACTOR__WATER_H__
#define __CLIENT__ACTOR__WATER_H__

#include "engine/actor/water.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CWater
			: public NSCore::CGameObject 
			, public NSEngine::NSActor::CWater {
		public:
			static CWater* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CWater(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CWater();

		};
		typedef CWater* pWater;

	}
}

#endif // !__CLIENT__ACTOR__WATER_H__
