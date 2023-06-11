#pragma once
#ifndef __ENGINE__ACTOR__POWER_UP_H__
#define __ENGINE__ACTOR__POWER_UP_H__

#include "engine/core/game_object.h"

#include "engine/component/loadable.h"
#include "engine/component/updatable.h"
#include "engine/component/renderable.h"
#include "engine/component/recordable.h"
#include "engine/component/physics.h"
#include "engine/component/sprite.h"

namespace NSEngine {
	namespace NSActor {

		struct CPowerUpRecord
			: public NSEngine::NSCore::CRecord {
			float position_x, position_y;

			CPowerUpRecord(
				uint32_t id
			);

			CPowerUpRecord(
				uint32_t id
				, float position_x, float position_y
			);
		};
		typedef CPowerUpRecord* pPowerUpRecord;

		class CPowerUp
			: public NSEngine::NSCore::CGameObject
			, public NSEngine::NSComponent::CLoadable
			, public NSEngine::NSComponent::CUpdatable
			, public NSEngine::NSComponent::CRenderable
			, public NSEngine::NSComponent::CRecordable
			, public NSEngine::NSComponent::CPhysics
			, public NSEngine::NSComponent::CSprite {
		public:
			CPowerUp(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CPowerUp();

			void Load(std::string data_path) override;
			void Unload() override;

			void PackLoad(NSEngine::NSNetworks::CPacket* packet) override;
			void UnpackLoad(NSEngine::NSNetworks::CPacket* packet) override;

			void Serialize(uint32_t tick) override;
			void Deserialize(NSEngine::NSCore::pRecord record) override;

			void PackRecord(
				NSEngine::NSNetworks::CPacket* packet
				, NSEngine::NSCore::pRecord record
			) override;

			void UnpackRecord(
				NSEngine::NSNetworks::CPacket* packet
				, NSEngine::NSCore::pRecord record
			) override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CPowerUp* pPowerUp;

	}
}

#endif // !__ENGINE__ACTOR__POWER_UP_H__
