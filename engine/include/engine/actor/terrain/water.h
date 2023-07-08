#pragma once
#ifndef __ENGINE__ACTOR__WATER_H__
#define __ENGINE__ACTOR__WATER_H__

#include "engine/core/game_object.h"

#include "engine/component/system/updatable.h"
#include "engine/component/system/physics.h"

#include "engine/component/render/renderable.h"
#include "engine/component/render/resource.h"

namespace NSEngine {
	namespace NSActor {

		class CWater
			: public NSCore::CGameObject

			, public NSComponent::CUpdatable
			, public NSComponent::CPhysics

			, public NSComponent::CRenderable
			, public NSComponent::CResource
		{
		protected:
			sf::Sprite sprite;

		public:
			CWater(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CWater();

			void LoadResource() override;
			void UnloadResource() override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSComponent::pPhysics other) override;
			void OnCollisionExit(NSComponent::pPhysics other) override;
		};
		typedef CWater* pWater;

	}
}

#endif // !__ENGINE__WATER_H__
