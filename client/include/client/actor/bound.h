#pragma once
#ifndef __CLIENT__ACTOR__BOUND_H__
#define __CLIENT__ACTOR__BOUND_H__

#include "engine/actor/bound.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CBound
			: public NSEngine::NSActor::CBound
			, public NSClient::NSCore::CGameObject {
		public:
			static CBound* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CBound(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CBound();

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CBound* pBound;

	}
}

#endif // !__CLIENT__ACTOR__BOUND_H__
