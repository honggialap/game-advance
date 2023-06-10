#pragma once
#ifndef __SERVER__ACTOR__TURRET_H__
#define __SERVER__ACTOR__TURRET_H__

#include "engine/actor/turret.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CTurret
			: public NSEngine::NSActor::CTurret
			, public NSServer::NSCore::CGameObject {
		public:
			static CTurret* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, nlohmann::json& data
			);

			CTurret(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
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

#endif // !__SERVER__ACTOR__TURRET_H__
