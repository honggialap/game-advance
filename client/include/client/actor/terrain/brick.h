#pragma once
#ifndef __CLIENT__ACTOR__BRICK_H__
#define __CLIENT__ACTOR__BRICK_H__

#include "client/core/game_object.h"
#include "engine/actor/terrain/brick.h"

namespace NSClient {
	namespace NSActor {

		class CBrick 
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CBrick
		{
		public:
			static CBrick* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CBrick(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CBrick();

		};
		typedef CBrick* pBrick;

	}
}

#endif // !__CLIENT__ACTOR__BRICK_H__
