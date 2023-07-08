#pragma once
#ifndef __ENGINE__ACTOR__STEEL_H__
#define __ENGINE__ACTOR__STEEL_H__

#include "engine/core/game_object.h"

#include "engine/component/system/updatable.h"
#include "engine/component/system/physics.h"
#include "engine/component/system/recordable.h"

#include "engine/component/render/renderable.h"
#include "engine/component/render/resource.h"

#include "engine/component/stat/defend_level.h"
#include "engine/component/stat/health.h"

namespace NSEngine {
	namespace NSActor {

		class CHeadquarter;
		typedef CHeadquarter* pHeadquarter;

		struct CSteelRecord
			: public NSCore::CRecord {
			CSteelRecord(uint32_t id);
		};
		typedef CSteelRecord* pSteelRecord;

		class CSteel
			: public NSCore::CGameObject

			, public NSComponent::CUpdatable
			, public NSComponent::CPhysics
			, public NSComponent::CRecordable

			, public NSComponent::CRenderable
			, public NSComponent::CResource

			, public NSComponent::CDefendLevel
			, public NSComponent::CHealth
		{
		protected:
			sf::Texture texture;
			sf::Sprite sprite;

			// Parent
			bool is_headquarter_bound = false;
			pHeadquarter headquarter = nullptr;

		public:
			CSteel(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CSteel();

			void AddHeadquarter(std::string name);

			void LoadResource() override;
			void UnloadResource() override;

			void Serialize(uint32_t tick) override;
			void Deserialize(NSCore::pRecord record) override;

			void PackRecord(NSNetworks::CPacket* packet, NSCore::pRecord record) override;
			NSCore::pRecord UnpackRecord(NSNetworks::CPacket* packet) override;

			void Update(float elapsed) override;
			void Render(sf::RenderWindow& window) override;

			void OnCollisionEnter(NSComponent::pPhysics other) override;
			void OnCollisionExit(NSComponent::pPhysics other) override;

			void PackLoadPacket(NSNetworks::CPacket* packet) override;
			void UnpackLoadPacket(NSNetworks::CPacket* packet) override;
		};
		typedef CSteel* pSteel;

	}
}

#endif // !__ENGINE__ACTOR__STEEL_H__
