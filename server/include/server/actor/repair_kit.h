#pragma once
#ifndef __SERVER__ACTOR__REPAIR_KIT_H__
#define __SERVER__ACTOR__REPAIR_KIT_H__

#include "engine/actor/repair_kit.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CRepairKit
			: public NSEngine::NSActor::CRepairKit
			, public NSServer::NSCore::CGameObject {
		public:
			static CRepairKit* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, std::string data_path
			);

			CRepairKit(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
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

#endif // !__SERVER__ACTOR__REPAIR_KIT_H__
