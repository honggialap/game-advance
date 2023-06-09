#pragma once	
#ifndef __CLIENT__ACTOR__CREEP_TANK_H__
#define __CLIENT__ACTOR__CREEP_TANK_H__

#include "engine/actor/creep_tank.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CCreepTank
			: public NSEngine::NSActor::CCreepTank
			, public NSClient::NSCore::CGameObject {
		public:
			static CCreepTank* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, std::string data_path
			);

			CCreepTank(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
			);
			~CCreepTank();

			void Load(std::string data_path) override;
			void Unload() override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CCreepTank* pCreepTank;

	}
}

#endif // !__CLIENT__ACTOR__CREEP_TANK_H__
