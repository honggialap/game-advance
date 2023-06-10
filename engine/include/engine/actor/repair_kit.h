#pragma once
#ifndef __ENGINE__ACTOR__REPAIR_KIT_H__
#define __ENGINE__ACTOR__REPAIR_KIT_H__

#include "engine/core/game_object.h"

#include "engine/component/loadable.h"
#include "engine/component/updatable.h"
#include "engine/component/renderable.h"
#include "engine/component/recordable.h"
#include "engine/component/physics.h"
#include "engine/component/sprite.h"

namespace NSEngine {
	namespace NSActor {

		struct CRepairKitRecord
			: public NSEngine::NSCore::CRecord {
			float position_x, position_y;

			CRepairKitRecord(
				uint32_t id
				, float position_x, float position_y
			);
		};
		typedef CRepairKitRecord* pRepairKitRecord;

		class CRepairKit
			: public NSEngine::NSCore::CGameObject
			, public NSEngine::NSComponent::CLoadable
			, public NSEngine::NSComponent::CUpdatable
			, public NSEngine::NSComponent::CRenderable
			, public NSEngine::NSComponent::CRecordable
			, public NSEngine::NSComponent::CPhysics
			, public NSEngine::NSComponent::CSprite {
		public:
			CRepairKit(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CRepairKit();

			void Load(std::string data_path) override;
			void Unload() override;

			void Serialize(uint32_t tick) override;
			void Deserialize(NSEngine::NSCore::pRecord record) override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CRepairKit* pRepairKit;

	}
}

#endif // !__ENGINE__ACTOR__REPAIR_KIT_H__
