#pragma once
#ifndef __SERVER__ACTOR__BOUND_H__
#define __SERVER__ACTOR__BOUND_H__

#include "engine/actor/bound.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CBound
			: public NSEngine::NSActor::CBound
			, public NSServer::NSCore::CGameObject {
		public:
			static CBound* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, std::string data_path
			);

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

#endif // !__SERVER__ACTOR__BOUND_H__
