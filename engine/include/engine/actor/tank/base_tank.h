#pragma once
#ifndef __ENGINE__ACTOR__BASE_TANK_H__
#define __ENGINE__ACTOR__BASE_TANK_H__

#include "engine/core/game_object.h"

#include "engine/component/system/updatable.h"
#include "engine/component/system/physics.h"
#include "engine/component/system/commandable.h"

#include "engine/component/render/renderable.h"
#include "engine/component/render/resource.h"

#include "engine/component/control/direction.h"
#include "engine/component/control/move.h"
#include "engine/component/control/shoot.h"

#include "engine/component/stat/defend_level.h"
#include "engine/component/stat/health.h"
#include "engine/component/stat/speed.h"

#include "engine/actor/tank/bullet.h"
#include "engine/actor/effect/explosion.h"

namespace NSEngine {
	namespace NSActor {

		class CGameMaster;
		typedef CGameMaster* pGameMaster;

		struct CMoveCommand
			: public NSCore::CCommand 
		{
			int32_t x;
			int32_t y;

			CMoveCommand(
				uint32_t game_object_id
				, int32_t x
				, int32_t y
			) :
				CCommand(game_object_id)
				, x(x)
				, y(y) 
			{
				command_type = ECommandType::TANK_MOVE;
			}
		};
		typedef CMoveCommand* pMoveCommand;

		struct CShootCommand
			: public NSCore::CCommand 
		{
			int32_t x;
			int32_t y;

			CShootCommand(
				uint32_t game_object_id
				, int32_t x
				, int32_t y
			) :
				CCommand(game_object_id),
				x(x),
				y(y)
			{
				command_type = ECommandType::TANK_SHOOT;
			}
		};
		typedef CShootCommand* pShootCommand;

		class CBaseTank
			: public NSCore::CGameObject

			, public NSComponent::CUpdatable
			, public NSComponent::CPhysics
			, public NSComponent::CCommandable

			, public NSComponent::CRenderable
			, public NSComponent::CResource
			
			, public NSComponent::CDirection
			, public NSComponent::CMove
			, public NSComponent::CShoot

			, public NSComponent::CDefendLevel
			, public NSComponent::CHealth
			, public NSComponent::CSpeed
		{
		protected:
			// Parent
			pGameMaster game_master = nullptr;

			// Children
			std::vector<pBullet> bullets;
			pExplosion explosion_effect = nullptr;

		public:
			CBaseTank(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CBaseTank();

			virtual void AddGameMaster(std::string name) = 0;

			void AddBullet(std::string name);
			void AddExplosionEffect(std::string name);

			void PackLoadPacket(NSNetworks::CPacket* packet) override;
			void UnpackLoadPacket(NSNetworks::CPacket* packet) override;
		};
		typedef CBaseTank* pBaseTank;

	}
}

#endif // !__ENGINE__ACTOR__BASE_TANK_H__
