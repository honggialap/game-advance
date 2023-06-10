#pragma once
#ifndef __CLIENT__ACTOR__WATER_H__
#define __CLIENT__ACTOR__WATER_H__

#include "engine/actor/water.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CWater
			: public NSEngine::NSActor::CWater
			, public NSClient::NSCore::CGameObject {
		public:
			static CWater* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, std::string data_path
			);

			CWater(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CWater();

			void Load(std::string data_path) override;
			void Unload() override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CWater* pWater;

	}
}

#endif // !__CLIENT__ACTOR__WATER_H__
