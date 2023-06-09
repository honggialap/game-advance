#pragma once
#ifndef __SERVER__CORE__GAME_OBJECT_H__
#define __SERVER__CORE__GAME_OBJECT_H__

#include "engine/common.h"
#include "engine/core/game_object.h"

namespace NSServer {
	namespace NSCore {

		class CGame;
		typedef CGame* pGame;
		class CWorld;
		typedef CWorld* pWorld;

		class CGameObject {
		protected:
			pGame game_server = nullptr;
			pWorld server_world = nullptr;

		public:
			CGameObject(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
			);
			virtual ~CGameObject() = 0;
		};
		typedef CGameObject* pGameObject;
		typedef std::unique_ptr<CGameObject> upGameObject;

	}
}

#endif // !__SERVER__CORE__GAME_OBJECT_H__
