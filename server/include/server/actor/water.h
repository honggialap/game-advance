#pragma once
#ifndef __SERVER__ACTOR__WATER_H__
#define __SERVER__ACTOR__WATER_H__

#include "engine/actor/water.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CWater
			: public NSEngine::NSActor::CWater
			, public NSServer::NSCore::CGameObject {
		public:
			static CWater* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, nlohmann::json& data
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

#endif // !__SERVER__ACTOR__WATER_H__
