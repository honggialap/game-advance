#pragma once
#ifndef __SERVER__ACTOR__POWER_UP_H__
#define __SERVER__ACTOR__POWER_UP_H__

#include "engine/actor/power_up.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CPowerUp
			: public NSEngine::NSActor::CPowerUp
			, public NSServer::NSCore::CGameObject {
		public:
			static CPowerUp* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, std::string data_path
			);

			CPowerUp(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
			);
			~CPowerUp();

			void Load(std::string data_path) override;
			void Unload() override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CPowerUp* pPowerUp;

	}
}

#endif // !__SERVER__ACTOR__POWER_UP_H__
