#pragma once
#ifndef __ENGINE__ACTOR__HEADQUARTER_H__
#define __ENGINE__ACTOR__HEADQUARTER_H__

#include "engine/core/game_object.h"

#include "engine/component/system/updatable.h"
#include "engine/component/system/recordable.h"
#include "engine/component/system/physics.h"

#include "engine/component/render/renderable.h"
#include "engine/component/render/resource.h"

#include "engine/actor/terrain/brick.h"
#include "engine/actor/terrain/steel.h"

namespace NSEngine {
	namespace NSActor {

		class CGameMaster;
		typedef CGameMaster* pGameMaster;

		struct CHeadquarterRecord
			: public NSCore::CRecord {

			bool is_alive = true;
			bool is_shovel_activated = false;
			float shovel_timer = 0.0f;

			CHeadquarterRecord(
				uint32_t id
			);

			CHeadquarterRecord(
				uint32_t id
				, bool is_alive
				, bool is_shovel_activated
				, float shovel_timer
			);
		};
		typedef CHeadquarterRecord* pHeadquarterRecord;

		class CHeadquarter
			: public NSCore::CGameObject

			, public NSComponent::CUpdatable
			, public NSComponent::CRecordable
			, public NSComponent::CPhysics
			
			, public NSComponent::CRenderable
			, public NSComponent::CResource
		{
		protected:
			std::map<uint32_t, sf::Sprite> sprites;

			// Parent
			pGameMaster game_master = nullptr;

			// Children
			std::vector<pBrick> bricks;
			std::vector<pSteel> steels;

			// Stats
			bool is_alive = true;
			bool is_shovel_activated = false;
			float shovel_default_timer = 0.0f;
			float shovel_timer = 0.0f;
			
		public:
			CHeadquarter(
				NSCore::pGame game
				, NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CHeadquarter();

			void AddGameMaster(std::string name);

			void AddBrick(std::string name);
			void AddSteel(std::string name);

			void ActivateShovel();
			void DeactivateShovel();

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

			void LoadComponents(nlohmann::json& components_data) override;
			void PackLoadPacket(NSNetworks::CPacket* packet) override;
			void UnpackLoadPacket(NSNetworks::CPacket* packet) override;
		};
		typedef CHeadquarter* pHeadquarter;

	}
}

#endif // !__ENGINE__ACTOR__HEADQUARTER_H__
