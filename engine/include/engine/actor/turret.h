#pragma once
#ifndef __ENGINE__ACTOR__TURRET_H__
#define __ENGINE__ACTOR__TURRET_H__

#include "engine/core/game_object.h"

#include "engine/component/networks_loadable.h"
#include "engine/component/updatable.h"
#include "engine/component/physics.h"
#include "engine/component/commandable.h"
#include "engine/component/recordable.h"
#include "engine/component/pooler.h"
#include "engine/component/resource_loadable.h"
#include "engine/component/sprite.h"
#include "engine/component/renderable.h"
#include "engine/component/team.h"
#include "engine/component/health.h"
#include "engine/component/ai_control.h"

namespace NSEngine {
	namespace NSActor {

		struct CTurretRecord
			: public NSCore::CRecord {
			CTurretRecord(uint32_t id);
		};
		typedef CTurretRecord* pTurretRecord;

		class CTurret
			: public NSCore::CGameObject
			, public NSComponent::CNetworksLoadable
			, public NSComponent::CUpdatable
			, public NSComponent::CPhysics
			, public NSComponent::CCommandable
			, public NSComponent::CRecordable
			, public NSComponent::CPooler
			, public NSComponent::CResourceLoadable
			, public NSComponent::CSprite
			, public NSComponent::CRenderable
			, public NSComponent::CTeam
			, public NSComponent::CHealth 
			, public NSComponent::CAIControl {
		public:
			CTurret(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CTurret();

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

			void ExecuteCommand(NSCore::pCommand command) override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSComponent::pPhysics other) override;
			void OnCollisionExit(NSComponent::pPhysics other) override;

			void PackNetworksLoadPacket(NSNetworks::CPacket* packet) override;
			void UnpackNetworksLoadPacket(NSNetworks::CPacket* packet) override;

		};
		typedef CTurret* pTurret;

	}
}

#endif // !__ENGINE__ACTOR__TURRET_H__
