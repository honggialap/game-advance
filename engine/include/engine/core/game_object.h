#pragma once
#ifndef __ENGINE__CORE__GAME_OBJECT_H__
#define __ENGINE__CORE__GAME_OBJECT_H__

#include "engine/common.h"
#include "engine/shared.h"

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

		public:
			CGameObject(pGame game, pWorld world);
			virtual ~CGameObject() = 0;

			void SetId(uint32_t value);
			uint32_t GetId();

			void SetType(EActorType value);
			EActorType GetType();

			void SetName(std::string value);
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
