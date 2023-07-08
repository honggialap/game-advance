#pragma once
#ifndef __CLIENT__ACTOR__STEEL_H__
#define __CLIENT__ACTOR__STEEL_H__

#include "client/core/game_object.h"
#include "engine/actor/terrain/steel.h"

namespace NSClient {
	namespace NSActor {

		class CSteel
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CSteel
		{
		public:
			static CSteel* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CSteel(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CSteel();

		};
		typedef CSteel* pSteel;

	}
}

#endif // !__CLIENT__ACTOR__STEEL_H__
