#pragma once
#ifndef __SERVER__ACTOR__BRICK_H__
#define __SERVER__ACTOR__BRICK_H__

#include "server/core/game_object.h"
#include "engine/actor/terrain/brick.h"

namespace NSServer {
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
				, nlohmann::json& components_data
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

#endif // !__SERVER__ACTOR__BRICK_H__
