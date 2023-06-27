#pragma once
#ifndef __ENGINE__ACTOR__REPAIR_KIT_H__
#define __ENGINE__ACTOR__REPAIR_KIT_H__

#include "engine/core/game_object.h"

#include "engine/component/updatable.h"
#include "engine/component/physics.h"
#include "engine/component/recordable.h"
#include "engine/component/resource_loadable.h"
#include "engine/component/animation.h"
#include "engine/component/renderable.h"

namespace NSEngine {
	namespace NSActor {

		struct CRepairKitRecord
			: public NSCore::CRecord {
			float position_x, position_y;

			CRepairKitRecord(
				uint32_t id
			);

			CRepairKitRecord(
				uint32_t id
				, float position_x, float position_y
			);
		};
		typedef CRepairKitRecord* pRepairKitRecord;

		class CRepairKit
			: public NSCore::CGameObject
			, public NSComponent::CUpdatable
			, public NSComponent::CPhysics
			, public NSComponent::CRecordable
			, public NSComponent::CResourceLoadable
			, public NSComponent::CAnimation 
			, public NSComponent::CRenderable {
		public:
			CRepairKit(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CRepairKit();

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
		typedef CRepairKit* pRepairKit;

	}
}

#endif // !__ENGINE__ACTOR__REPAIR_KIT_H__
