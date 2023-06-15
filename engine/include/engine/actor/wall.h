#pragma once
#ifndef __ENGINE__ACTOR__WALL_H__
#define __ENGINE__ACTOR__WALL_H__

#include "engine/core/game_object.h"

#include "engine/component/networks_loadable.h"
#include "engine/component/updatable.h"
#include "engine/component/physics.h"
#include "engine/component/recordable.h"
#include "engine/component/resource_loadable.h"
#include "engine/component/sprite.h"
#include "engine/component/renderable.h"
#include "engine/component/health.h"

namespace NSEngine {
	namespace NSActor {

		struct CWallRecord 
			: public NSCore::CRecord {
			CWallRecord(uint32_t id);
		};
		typedef CWallRecord* pWallRecord;

		class CWall
			: public NSCore::CGameObject
			, public NSComponent::CNetworksLoadable
			, public NSComponent::CUpdatable
			, public NSComponent::CPhysics
			, public NSComponent::CRecordable
			, public NSComponent::CResourceLoadable
			, public NSComponent::CSprite
			, public NSComponent::CRenderable
			, public NSComponent::CHealth {
		public:
			CWall(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CWall();

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

			void PackNetworksLoadPacket(NSNetworks::CPacket* packet) override;
			void UnpackNetworksLoadPacket(NSNetworks::CPacket* packet) override;

		};
		typedef CWall* pWall;

	}
}

#endif // !__ENGINE__ACTOR__WALL_H__
