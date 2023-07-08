#pragma once
#ifndef __CLIENT__ACTOR__TREE_H__
#define __CLIENT__ACTOR__TREE_H__

#include "client/core/game_object.h"
#include "engine/actor/terrain/tree.h"

namespace NSClient {
	namespace NSActor {

		class CTree
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CTree 
		{
		public:
			static CTree* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CTree(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CTree();

		};
		typedef CTree* pTree;

	}
}

#endif // !__CLIENT__ACTOR__TREE_H__
