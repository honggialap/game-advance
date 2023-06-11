#pragma once
#ifndef __CLIENT__ACTOR__FACTORY_H__
#define __CLIENT__ACTOR__FACTORY_H__

#include "engine/actor/factory.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CFactory
			: public NSEngine::NSActor::CFactory
			, public NSClient::NSCore::CGameObject {
		public:
			static CFactory* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
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

#endif // !__CLIENT__ACTOR__FACTORY_H__
