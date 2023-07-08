#pragma once
#ifndef __ENGINE__ACTOR__EXPLOSION_H__
#define __ENGINE__ACTOR__EXPLOSION_H__

#include "engine/core/game_object.h"

#include "engine/component/system/updatable.h"
#include "engine/component/system/physics.h"

#include "engine/component/render/renderable.h"
#include "engine/component/render/resource.h"

namespace NSEngine {
	namespace NSActor {

		class CBaseTank;
		typedef CBaseTank* pBaseTank;

		class CExplosion
			: public NSCore::CGameObject

			, public NSComponent::CUpdatable
			, public NSComponent::CRenderable
			, public NSComponent::CResource
		{
		protected:
			float x = 0.0f;
			float y = 0.0f;

			pBaseTank base_tank = nullptr;

		public:
			CExplosion(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CExplosion();

			void AddBaseTank(std::string name);

			void SetPosition(float value_x, float value_y);
			void GetPosition(float& out_x, float& out_y);

			void LoadResource() override;
			void UnloadResource() override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void PackLoadPacket(NSNetworks::CPacket* packet) override;
			void UnpackLoadPacket(NSNetworks::CPacket* packet) override;
		};
		typedef CExplosion* pExplosion;

	}
}

#endif // !__ENGINE__ACTOR__EXPLOSION_H__
