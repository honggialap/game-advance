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
			, public NSEngine::NSComponent::CLoadable
			, public NSEngine::NSComponent::CPhysics {
		public:
			CBound(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
			);
			~CBound();

			void Load(std::string data_path) override;
			void Unload() override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CBound* pBound;

	}
}

#endif // !__ENGINE__ACTOR__BOUND_H__
