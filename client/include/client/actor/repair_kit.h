#pragma once
#ifndef __CLIENT__ACTOR__REPAIR_KIT_H__
#define __CLIENT__ACTOR__REPAIR_KIT_H__

#include "engine/actor/repair_kit.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CRepairKit
			: public NSEngine::NSActor::CRepairKit
			, public NSClient::NSCore::CGameObject {
		public:
			static CRepairKit* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CRepairKit(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CRepairKit();

			void Load(std::string data_path) override;
			void Unload() override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CRepairKit* pRepairKit;

	}
}

#endif // !__CLIENT__ACTOR__REPAIR_KIT_H__
