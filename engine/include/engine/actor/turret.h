#pragma once
#ifndef __ENGINE__ACTOR__TURRET_H__
#define __ENGINE__ACTOR__TURRET_H__

#include "engine/core/game_object.h"

#include "engine/component/loadable.h"
#include "engine/component/updatable.h"
#include "engine/component/renderable.h"
#include "engine/component/recordable.h"
#include "engine/component/physics.h"
#include "engine/component/sprite.h"
#include "engine/component/team.h"
#include "engine/component/health.h"

namespace NSEngine {
	namespace NSActor {

		struct CTurretRecord
			: public NSEngine::NSCore::CRecord {
			CTurretRecord(uint32_t id);
		};
		typedef CTurretRecord* pTurretRecord;

		class CTurret
			: public NSEngine::NSCore::CGameObject
			, public NSEngine::NSComponent::CLoadable
			, public NSEngine::NSComponent::CUpdatable
			, public NSEngine::NSComponent::CRenderable
			, public NSEngine::NSComponent::CRecordable
			, public NSEngine::NSComponent::CPhysics
			, public NSEngine::NSComponent::CSprite
			, public NSEngine::NSComponent::CTeam
			, public NSEngine::NSComponent::CHealth {
		public:
			CTurret(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CTurret();

			void Load(std::string data_path) override;
			void Unload() override;

			void Serialize(uint32_t tick) override;
			void Deserialize(NSEngine::NSCore::pRecord record) override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSEngine::NSComponent::pPhysics other) override;
			void OnCollisionExit(NSEngine::NSComponent::pPhysics other) override;
		};
		typedef CTurret* pTurret;

	}
}

#endif // !__ENGINE__ACTOR__TURRET_H__
