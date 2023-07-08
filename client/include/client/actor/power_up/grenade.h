#pragma once
#ifndef __CLIENT__ACTOR__GRENADE_H__
#define __CLIENT__ACTOR__GRENADE_H__

#include "client/core/game_object.h"
#include "engine/actor/power_up/grenade.h"

namespace NSClient {
	namespace NSActor {

		class CGrenade
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CGrenade
		{
		public:
			static CGrenade* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CGrenade(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CGrenade();

		};
		typedef CGrenade* pGrenade;

	}
}

#endif // !__CLIENT__ACTOR__GRENADE_H__
