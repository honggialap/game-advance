#pragma once
#ifndef __SERVER__ACTOR__HEADQUARTER_H__
#define __SERVER__ACTOR__HEADQUARTER_H__

#include "engine/actor/headquarter.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CHeadquarter
			: public NSEngine::NSActor::CHeadquarter
			, public NSServer::NSCore::CGameObject {
		public:
			static CHeadquarter* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, nlohmann::json& data
			);

			CHeadquarter(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CHeadquarter();

			void Load(std::string data_path) override;
			void Unload() override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CHeadquarter* pHeadquarter;

	}
}

#endif // !__SERVER__ACTOR__HEADQUARTER_H__
