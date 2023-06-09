#pragma once
#ifndef __SERVER__ACTOR__TREE_H__
#define __SERVER__ACTOR__TREE_H__

#include "engine/actor/tree.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CTree
			: public NSEngine::NSActor::CTree
			, public NSServer::NSCore::CGameObject {
		public:
			static CTree* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, std::string data_path
			);

			CTree(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
			);
			~CTree();

			void Load(std::string data_path) override;
			void Unload() override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CTree* pTree;

	}
}

#endif // !__SERVER__ACTOR__TREE_H__
