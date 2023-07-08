#pragma once
#ifndef __SERVER__ACTOR__GRENADE_H__
#define __SERVER__ACTOR__GRENADE_H__

#include "server/core/game_object.h"
#include "engine/actor/power_up/grenade.h"

namespace NSServer {
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
				, nlohmann::json& components_data
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

#endif // !__SERVER__ACTOR__GRENADE_H__
