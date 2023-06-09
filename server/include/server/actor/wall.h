#pragma once
#ifndef __SERVER__ACTOR__WALL_H__
#define __SERVER__ACTOR__WALL_H__

#include "engine/actor/wall.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CWall
			: public NSEngine::NSActor::CWall
			, public NSServer::NSCore::CGameObject {
		public:
			static CWall* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
				, std::string data_path
			);

			CWall(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
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

#endif // !__SERVER__ACTOR__WALL_H__
