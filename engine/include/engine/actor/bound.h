#pragma once
#ifndef __ENGINE__ACTOR__BOUND_H__
#define __ENGINE__ACTOR__BOUND_H__

#include "engine/core/game_object.h"

#include "engine/component/loadable.h"
#include "engine/component/physics.h"

namespace NSEngine {
	namespace NSActor {

		class CBound
			: public NSEngine::NSCore::CGameObject
			, public NSEngine::NSComponent::CPhysics {
		public:
			CBound(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CBound();

			void PackLoad(NSEngine::NSNetworks::CPacket* packet) override;
			void UnpackLoad(NSEngine::NSNetworks::CPacket* packet) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CBound* pBound;

	}
}

#endif // !__ENGINE__ACTOR__BOUND_H__
