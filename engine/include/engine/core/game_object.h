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

			bool is_active;
			bool is_destroyed;

			uint32_t parent_id;
			std::vector<uint32_t> children_id;

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

			void SetActive(bool value);
			bool IsActive();

			void Destroy();
			bool IsDestroyed();
		};
		typedef CGameObject* pGameObject;
		typedef std::unique_ptr<CGameObject> upGameObject;

	}
}

#endif // !__ENGINE__CORE__GAME_OBJECT_H__
