#pragma once
#ifndef __ENGINE__ACTOR__BULLET_H__
#define __ENGINE__ACTOR__BULLET_H__

#include "engine/core/game_object.h"

#include "engine/component/system/updatable.h"
#include "engine/component/system/physics.h"
#include "engine/component/system/recordable.h"

#include "engine/component/render/renderable.h"
#include "engine/component/render/resource.h"

#include "engine/component/control/direction.h"

#include "engine/component/stat/attack_level.h"
#include "engine/component/stat/damage.h"
#include "engine/component/stat/speed.h"

#include "engine/actor/effect/impact.h"

namespace NSEngine {
	namespace NSActor {

		class CBaseTank;
		typedef CBaseTank* pBaseTank;

		struct CBulletRecord
			: public NSCore::CRecord {
			float position_x, position_y;
			float velocity_x, velocity_y;

			CBulletRecord(
				uint32_t id
			);

			CBulletRecord(
				uint32_t id
				, float position_x, float position_y
				, float velocity_x, float velocity_y
			);
		};
		typedef CBulletRecord* pBulletRecord;

		class CBullet
			: public NSCore::CGameObject

			, public NSComponent::CUpdatable
			, public NSComponent::CPhysics
			, public NSComponent::CRecordable

			, public NSComponent::CRenderable
			, public NSComponent::CResource

			, public NSComponent::CDirection

			, public NSComponent::CAttackLevel
			, public NSComponent::CDamage
			, public NSComponent::CSpeed
		{
		protected:
			std::map<uint32_t, sf::Sprite> sprites;

			// Parent
			pBaseTank base_tank = nullptr;

			// Children
			pImpact impact_effect = nullptr;

		public:
			CBullet(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CBullet();

			void AddBaseTank(std::string name);

			void AddImpactEffect(std::string name);

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

			void PackLoadPacket(NSNetworks::CPacket* packet) override;
			void UnpackLoadPacket(NSNetworks::CPacket* packet) override;
		};
		typedef CBullet* pBullet;

	}
}

#endif // !__ENGINE__ACTOR__BULLET_H__
