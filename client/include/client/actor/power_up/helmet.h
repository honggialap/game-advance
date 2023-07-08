#pragma once
#ifndef __CLIENT__ACTOR__HELMET_H__
#define __CLIENT__ACTOR__HELMET_H__

#include "client/core/game_object.h"
#include "engine/actor/power_up/helmet.h"

namespace NSClient {
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

#endif // !__CLIENT__ACTOR__HELMET_H__
