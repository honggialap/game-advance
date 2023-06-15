#pragma once
#ifndef __ENGINE__ACTOR__WATER_H__
#define __ENGINE__ACTOR__WATER_H__

#include "engine/core/game_object.h"

#include "engine/component/networks_loadable.h"
#include "engine/component/updatable.h"
#include "engine/component/physics.h"
#include "engine/component/resource_loadable.h"
#include "engine/component/sprite.h"
#include "engine/component/renderable.h"

namespace NSEngine {
	namespace NSActor {

		class CWater
			: public NSCore::CGameObject
			, public NSComponent::CNetworksLoadable
			, public NSComponent::CUpdatable
			, public NSComponent::CPhysics
			, public NSComponent::CResourceLoadable
			, public NSComponent::CSprite 
			, public NSComponent::CRenderable {
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

			void PackNetworksLoadPacket(NSNetworks::CPacket* packet) override;
			void UnpackNetworksLoadPacket(NSNetworks::CPacket* packet) override;

		};
		typedef CWater* pWater;

	}
}

#endif // !__ENGINE__WATER_H__
