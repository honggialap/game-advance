#pragma once
#ifndef __CLIENT__ACTOR__SCORE_H__
#define __CLIENT__ACTOR__SCORE_H__

#include "client/core/game_object.h"
#include "engine/actor/effect/score.h"

namespace NSClient {
	namespace NSActor {

		class CScore
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CScore
		{
		public:
			static CScore* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CScore(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CScore();

		};
		typedef CScore* pScore;

	}
}

#endif // !__CLIENT__ACTOR__SCORE_H__
