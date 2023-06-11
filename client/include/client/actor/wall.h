#pragma once
#ifndef __CLIENT__ACTOR__WALL_H__
#define __CLIENT__ACTOR__WALL_H__

#include "engine/actor/wall.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CWall
			: public NSEngine::NSActor::CWall
			, public NSClient::NSCore::CGameObject {
		public:
			static CWall* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CWall(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CWall();

			void Load(std::string data_path) override;
			void Unload() override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CWall* pWall;

	}
}

#endif // !__CLIENT__ACTOR__WALL_H__
