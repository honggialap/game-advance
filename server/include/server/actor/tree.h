#pragma once
#ifndef __SERVER__ACTOR__TREE_H__
#define __SERVER__ACTOR__TREE_H__

#include "engine/actor/tree.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CTree
			: public NSCore::CGameObject
			, public NSEngine::NSActor::CTree {
		public:
			static CTree* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, nlohmann::json& components_data
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

#endif // !__SERVER__ACTOR__TREE_H__
