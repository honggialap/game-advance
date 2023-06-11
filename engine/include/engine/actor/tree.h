#pragma once
#ifndef __ENGINE__ACTOR__TREE_H__
#define __ENGINE__ACTOR__TREE_H__

#include "engine/core/game_object.h"

#include "engine/component/loadable.h"
#include "engine/component/updatable.h"
#include "engine/component/renderable.h"
#include "engine/component/physics.h"
#include "engine/component/sprite.h"

namespace NSEngine {
	namespace NSActor {

		class CTree
			: public NSEngine::NSCore::CGameObject
			, public NSEngine::NSComponent::CLoadable
			, public NSEngine::NSComponent::CUpdatable
			, public NSEngine::NSComponent::CRenderable
			, public NSEngine::NSComponent::CPhysics
			, public NSEngine::NSComponent::CSprite {
		public:
			CTree(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CTree();

			void Load(std::string data_path) override;
			void Unload() override;

			void PackLoad(NSEngine::NSNetworks::CPacket* packet) override;
			void UnpackLoad(NSEngine::NSNetworks::CPacket* packet) override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CTree* pTree;

	}
}

#endif // !__ENGINE__ACTOR__TREE_H__
