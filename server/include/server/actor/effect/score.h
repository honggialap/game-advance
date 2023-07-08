#pragma once
#ifndef __SERVER__ACTOR__SCORE_H__
#define __SERVER__ACTOR__SCORE_H__

#include "server/core/game_object.h"
#include "engine/actor/effect/score.h"

namespace NSServer {
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
				, nlohmann::json& components_data
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

#endif // !__SERVER__ACTOR__SCORE_H__
