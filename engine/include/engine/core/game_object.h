#pragma once
#ifndef __ENGINE__CORE__GAME_OBJECT_H__
#define __ENGINE__CORE__GAME_OBJECT_H__

#include "engine/common.h"
#include "engine/shared.h"
#include "engine/networks/packet.h"

namespace NSEngine {
	namespace NSCore {

		class CGame;
		typedef CGame* pGame;

		class CWorld;
		typedef CWorld* pWorld;

		class CGameObject {
		protected:
			pGame game;
			pWorld world;

			uint32_t id;
			EActorType type;
			std::string name;

			bool is_destroyed;

			std::string parent_name;
			std::vector<std::string> children_name;

		public:
			CGameObject(
				pGame game
				, pWorld world
				, uint32_t id
				, std::string name
			);
			virtual ~CGameObject() = 0;

			uint32_t GetId();
			EActorType GetType();
			std::string GetName();

			void Destroy();
			bool IsDestroyed();

			bool AddParent(std::string parent_name_value);
			bool RemoveParent();
			bool ChangeParent(std::string new_parent_name_value);
			CGameObject* GetParent();

			bool AddChild(std::string child_name_value);
			bool RemoveChild(std::string child_name_value);
			CGameObject* GetChild(std::string child_name_value);

			void LoadComponents(nlohmann::json& components_data);

			virtual void PackLoadPacket(NSNetworks::CPacket* packet);
			virtual void UnpackLoadPacket(NSNetworks::CPacket* packet);
		};
		typedef CGameObject* pGameObject;
		typedef std::unique_ptr<CGameObject> upGameObject;

	}
}

#endif // !__ENGINE__CORE__GAME_OBJECT_H__
