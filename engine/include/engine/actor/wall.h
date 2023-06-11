#pragma once
#ifndef __ENGINE__ACTOR__WALL_H__
#define __ENGINE__ACTOR__WALL_H__

#include "engine/core/game_object.h"

#include "engine/component/loadable.h"
#include "engine/component/updatable.h"
#include "engine/component/renderable.h"
#include "engine/component/recordable.h"
#include "engine/component/physics.h"
#include "engine/component/sprite.h"
#include "engine/component/health.h"

namespace NSEngine {
	namespace NSActor {

		struct CWallRecord 
			: public NSEngine::NSCore::CRecord {
			CWallRecord(uint32_t id);
		};
		typedef CWallRecord* pWallRecord;

		class CWall
			: public NSEngine::NSCore::CGameObject
			, public NSEngine::NSComponent::CLoadable
			, public NSEngine::NSComponent::CUpdatable
			, public NSEngine::NSComponent::CRenderable
			, public NSEngine::NSComponent::CRecordable
			, public NSEngine::NSComponent::CPhysics
			, public NSEngine::NSComponent::CSprite
			, public NSEngine::NSComponent::CHealth {
		public:
			CWall(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CWall();

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
		typedef CWall* pWall;

	}
}

#endif // !__ENGINE__ACTOR__WALL_H__
