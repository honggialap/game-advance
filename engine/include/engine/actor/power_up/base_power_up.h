#pragma once
#ifndef __ENGINE__ACTOR__BASE_POWER_UP_H__
#define __ENGINE__ACTOR__BASE_POWER_UP_H__

#include "engine/core/game_object.h"

#include "engine/component/system/updatable.h"
#include "engine/component/system/physics.h"

#include "engine/component/render/renderable.h"
#include "engine/component/render/resource.h"

namespace NSEngine {
	namespace NSActor {

		class CGameMaster;
		typedef CGameMaster* pGameMaster;

		class CBasePowerUp
			: public NSCore::CGameObject

			, public NSComponent::CUpdatable
			, public NSComponent::CPhysics

			, public NSComponent::CRenderable
			, public NSComponent::CResource
		{
		protected:
			sf::Texture texture;
			sf::Sprite sprite;

			// Parent
			pGameMaster game_master = nullptr;

		public:
			CBasePowerUp(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CBasePowerUp();

			void AddGameMaster(std::string name);

			void LoadResource() override;
			void UnloadResource() override;

			void PackLoadPacket(NSNetworks::CPacket* packet) override;
			void UnpackLoadPacket(NSNetworks::CPacket* packet) override;
		};
		typedef CBasePowerUp* pBasePowerUp;

	}
}

#endif // !__ENGINE__ACTOR__BASE_POWER_UP_H__
