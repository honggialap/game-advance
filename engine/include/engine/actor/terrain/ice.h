#pragma once
#ifndef __ENGINE__ACTOR__ICE_H__
#define __ENGINE__ACTOR__ICE_H__

#include "engine/core/game_object.h"

#include "engine/component/system/physics.h"

#include "engine/component/render/renderable.h"
#include "engine/component/render/resource.h"

namespace NSEngine {
	namespace NSActor {

		class CIce
			: public NSCore::CGameObject
			, public NSComponent::CRenderable
			, public NSComponent::CResource
		{
		protected:
			sf::Texture texture;
			sf::Sprite sprite;

			float x;
			float y;

		public:
			CIce(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CIce();

			void SetPosition(float value_x, float value_y);
			void GetPosition(float& out_x, float out_y);

			void LoadResource() override;
			void UnloadResource() override;

			void Render(sf::RenderWindow& window) override;
		};
		typedef CIce* pIce;

	}
}

#endif // !__ENGINE__ACTOR__ICE_H__
