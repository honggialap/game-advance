#pragma once
#ifndef __SERVER__ACTOR__FACTORY_H__
#define __SERVER__ACTOR__FACTORY_H__

#include "engine/actor/factory.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CFactory
			: public NSEngine::NSActor::CFactory
			, public NSServer::NSCore::CGameObject {
		public:
			static CFactory* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, nlohmann::json& data
			);

			CFactory(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CFactory();

			void Load(std::string data_path) override;
			void Unload() override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CFactory* pFactory;

	}
}

#endif // !__SERVER_FACTORY_H__
