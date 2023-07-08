#pragma once
#ifndef __CLIENT__ACTOR__STAR_H__
#define __CLIENT__ACTOR__STAR_H__

#include "client/core/game_object.h"
#include "engine/actor/power_up/star.h"

namespace NSClient {
	namespace NSActor {

		class CStar
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CStar
		{
		public:
			static CStar* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CStar(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CStar();

		};
		typedef CStar* pStar;

	}
}

#endif // !__CLIENT__ACTOR__STAR_H__
