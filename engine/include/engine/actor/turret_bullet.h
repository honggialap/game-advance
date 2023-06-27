#pragma once
#ifndef __ENGINE__ACTOR__TURRET_BULLET_H__
#define __ENGINE__ACTOR__TURRET_BULLET_H__

#include "engine/core/game_object.h"

#include "engine/component/updatable.h"
#include "engine/component/physics.h"
#include "engine/component/recordable.h"
#include "engine/component/resource_loadable.h"
#include "engine/component/renderable.h"
#include "engine/component/animation.h"
#include "engine/component/team.h"
#include "engine/component/damage.h"

namespace NSEngine {
	namespace NSActor {

		struct CTurretBulletRecord 
			: public NSCore::CRecord {
			float position_x, position_y;
			float velocity_x, velocity_y;

			CTurretBulletRecord(
				uint32_t id
			);

			CTurretBulletRecord(
				uint32_t id
				, float position_x, float position_y
				, float velocity_x, float velocity_y
			);
		};
		typedef CTurretBulletRecord* pTurretBulletRecord;

		class CTurretBullet
			: public NSCore::CGameObject
			, public NSComponent::CUpdatable
			, public NSComponent::CPhysics
			, public NSComponent::CRecordable
			, public NSComponent::CResourceLoadable
			, public NSComponent::CSprite
			, public NSComponent::CRenderable
			, public NSComponent::CTeam
			, public NSComponent::CDamage {
		public:
			CTurretBullet(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CTurretBullet();

			void LoadResource() override;
			void UnloadResource() override;

			void Serialize(uint32_t tick) override;
			void Deserialize(NSCore::pRecord record) override;

			void PackRecord(
				NSNetworks::CPacket* packet
				, NSCore::pRecord record
			) override;

			NSCore::pRecord UnpackRecord(
				NSNetworks::CPacket* packet
			) override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSComponent::pPhysics other) override;
			void OnCollisionExit(NSComponent::pPhysics other) override;
		};
		typedef CTurretBullet* pTurretBullet;

	}
}

#endif // !__ENGINE__ACTOR__TURRET_BULLET_H__
