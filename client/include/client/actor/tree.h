#pragma once
#ifndef __CLIENT__ACTOR__TREE_H__
#define __CLIENT__ACTOR__TREE_H__

#include "engine/actor/tree.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CTree
			: public NSEngine::NSActor::CTree
			, public NSClient::NSCore::CGameObject {
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

#endif // !__CLIENT__ACTOR__TREE_H__
