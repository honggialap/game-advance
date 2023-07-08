#pragma once
#ifndef __ENGINE__ACTOR__BOUND_H__
#define __ENGINE__ACTOR__BOUND_H__

#include "engine/core/game_object.h"

#include "engine/component/system/physics.h"

namespace NSEngine {
	namespace NSActor {

		class CBound
			: public NSCore::CGameObject
			
			, public NSComponent::CPhysics
		{
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
		};
		typedef CBound* pBound;

	}
}

#endif // !__ENGINE__ACTOR__BOUND_H__
