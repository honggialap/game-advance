#pragma once
#ifndef __SERVER__ACTOR__WALL_H__
#define __SERVER__ACTOR__WALL_H__

#include "engine/actor/wall.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CWall
			: public NSCore::CGameObject 
			, public NSEngine::NSActor::CWall {
		public:
			static CWall* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, nlohmann::json& components_data
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

#endif // !__SERVER__ACTOR__WALL_H__
