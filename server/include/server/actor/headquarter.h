#pragma once
#ifndef __SERVER__ACTOR__HEADQUARTER_H__
#define __SERVER__ACTOR__HEADQUARTER_H__

#include "server/core/game_object.h"
#include "engine/actor/headquarter.h"

namespace NSServer {
	namespace NSActor {

		class CHeadquarter
			: public NSCore::CGameObject 
			, public NSEngine::NSActor::CHeadquarter
		{
		public:
			static CHeadquarter* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, nlohmann::json& components_data
			);

			CHeadquarter(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CHeadquarter();

			void Update(float elapsed) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;

		};
		typedef CHeadquarter* pHeadquarter;

	}
}

#endif // !__SERVER__ACTOR__HEADQUARTER_H__
