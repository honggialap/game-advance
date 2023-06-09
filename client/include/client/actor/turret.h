#pragma once
#ifndef __CLIENT__ACTOR__TURRET_H__
#define __CLIENT__ACTOR__TURRET_H__

#include "engine/actor/turret.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CTurret
			: public NSEngine::NSActor::CTurret
			, public NSClient::NSCore::CGameObject {
		public:
			static CTurret* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, std::string data_path
			);

			CTurret(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
			);
			~CTurret();

			void Load(std::string data_path) override;
			void Unload() override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CTurret* pTurret;

	}
}

#endif // !__CLIENT__ACTOR__TURRET_H__
