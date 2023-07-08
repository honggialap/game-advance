#pragma once
#ifndef __ENGINE__ACTOR__TREE_H__
#define __ENGINE__ACTOR__TREE_H__

#include "engine/core/game_object.h"

#include "engine/component/system/physics.h"

#include "engine/component/render/renderable.h"
#include "engine/component/render/resource.h"

namespace NSEngine {
	namespace NSActor {

		class CTree
			: public NSCore::CGameObject
			, public NSComponent::CRenderable
			, public NSComponent::CResource
		{
		protected:
			sf::Sprite sprite;

			float x;
			float y;

		public:
			CTree(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CTree();

			void SetPosition(float value_x, float value_y);
			void GetPosition(float& out_x, float out_y);

			void LoadResource() override;
			void UnloadResource() override;

			void Render(sf::RenderWindow& window) override;
		};
		typedef CTree* pTree;

	}
}

#endif // !__ENGINE__ACTOR__TREE_H__
