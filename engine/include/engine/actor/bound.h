#pragma once
#ifndef __ENGINE__ACTOR__BOUND_H__
#define __ENGINE__ACTOR__BOUND_H__

#include "engine/core/game_object.h"
#include "engine/component/physics.h"
#include "engine/component/networks_loadable.h"

namespace NSEngine {
	namespace NSActor {

		class CBound
			: public NSCore::CGameObject
			, public NSComponent::CPhysics 
			, public NSComponent::CNetworksLoadable {
		public:
			CBound(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CBound();

			void OnCollisionEnter(NSComponent::pPhysics other) override;
			void OnCollisionExit(NSComponent::pPhysics other) override;

			void PackNetworksLoadPacket(NSNetworks::CPacket* packet) override;
			void UnpackNetworksLoadPacket(NSNetworks::CPacket* packet) override;
		};
		typedef CBound* pBound;

	}
}

#endif // !__ENGINE__ACTOR__BOUND_H__
