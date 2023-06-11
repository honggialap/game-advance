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

			virtual void PackLoad(NSEngine::NSNetworks::CPacket* packet) = 0;
			virtual void UnpackLoad(NSEngine::NSNetworks::CPacket* packet) = 0;
		};
		typedef CGameObject* pGameObject;
		typedef std::unique_ptr<CGameObject> upGameObject;

	}
}

#endif // !__ENGINE__CORE__GAME_OBJECT_H__
