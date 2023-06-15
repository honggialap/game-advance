#pragma once
#ifndef __CLIENT__ACTOR__WALL_H__
#define __CLIENT__ACTOR__WALL_H__

#include "engine/actor/wall.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CWall 
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CWall
		{
		public:
			static CWall* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CWall(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CWall();

		};
		typedef CWall* pWall;

	}
}

#endif // !__CLIENT__ACTOR__WALL_H__
