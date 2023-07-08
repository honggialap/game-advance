#pragma once
#ifndef __ENGINE__ACTOR__PLAYER_TANK_H__
#define __ENGINE__ACTOR__PLAYER_TANK_H__

#include "engine/actor/tank/base_tank.h"

#include "engine/component/system/recordable.h"
#include "engine/component/control/player_control.h"
#include "engine/component/stat/power_level.h"

namespace NSEngine {
	namespace NSActor {

		struct CPlayerTankRecord 
			: public NSCore::CRecord {
			float position_x, position_y;
			float velocity_x, velocity_y;
			int32_t movement_x, movement_y;

			CPlayerTankRecord(
				uint32_t id
			);

			CPlayerTankRecord(
				uint32_t id
				, float position_x, float position_y
				, float velocity_x, float velocity_y
				, int32_t movement_x, int32_t movement_y
			);
		};
		typedef CPlayerTankRecord* pPlayerTankRecord;

		class CPlayerTank
			: public NSActor::CBaseTank

			, public NSComponent::CRecordable
			, public NSComponent::CPlayerControl
			, public NSComponent::CPowerLevel
		{
		protected:
			std::map<uint32_t, sf::Sprite> tank_sprites;
			//sf::Sprite shield_sprite;

		public:
			CPlayerTank(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CPlayerTank();

			void AddGameMaster(std::string name) final;

			void LoadResource() override;
			void UnloadResource() override;

			void Serialize(uint32_t tick) override;
			void Deserialize(NSEngine::NSCore::pRecord record) override;

			void ExecuteCommand(NSEngine::NSCore::pCommand command) override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void PackRecord(
				NSEngine::NSNetworks::CPacket* packet
				, NSEngine::NSCore::pRecord record
			) override;

			NSEngine::NSCore::pRecord UnpackRecord(
				NSEngine::NSNetworks::CPacket* packet
			) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CPlayerTank* pPlayerTank;

	}
}

#endif // !__ENGINE__ACTOR__PLAYER_TANK_H__
