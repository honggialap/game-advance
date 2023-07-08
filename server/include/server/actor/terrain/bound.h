#pragma once
#ifndef __SERVER__ACTOR__BOUND_H__
#define __SERVER__ACTOR__BOUND_H__

#include "server/core/game_object.h"
#include "engine/actor/terrain/bound.h"

namespace NSServer {
	namespace NSActor {

		class CBound
			: public NSCore::CGameObject 
			, public NSEngine::NSActor::CBound
		{
		public:
			static CBound* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, nlohmann::json& components_data
			);

			CBound(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CBound();

		};
		typedef CBound* pBound;

	}
}

#endif // !__SERVER__ACTOR__BOUND_H__
