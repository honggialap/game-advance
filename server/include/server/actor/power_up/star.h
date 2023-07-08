#pragma once
#ifndef __SERVER__ACTOR__STAR_H__
#define __SERVER__ACTOR__STAR_H__

#include "server/core/game_object.h"
#include "engine/actor/power_up/star.h"

namespace NSServer {
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
				, nlohmann::json& components_data
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

#endif // !__SERVER__ACTOR__STAR_H__
