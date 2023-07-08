#pragma once
#ifndef __SERVER__ACTOR__HELMET_H__
#define __SERVER__ACTOR__HELMET_H__

#include "server/core/game_object.h"
#include "engine/actor/power_up/helmet.h"

namespace NSServer {
	namespace NSActor {

		class CHelmet
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CHelmet
		{
		public:
			static CHelmet* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, nlohmann::json& components_data
			);

			CHelmet(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CHelmet();

		};
		typedef CHelmet* pHelmet;

	}
}

#endif // !__SERVER__ACTOR__HELMET_H__
