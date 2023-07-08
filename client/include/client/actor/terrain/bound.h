#pragma once
#ifndef __CLIENT__ACTOR__BOUND_H__
#define __CLIENT__ACTOR__BOUND_H__

#include "client/core/game_object.h"
#include "engine/actor/terrain/bound.h"

namespace NSClient {
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

#endif // !__CLIENT__ACTOR__BOUND_H__
