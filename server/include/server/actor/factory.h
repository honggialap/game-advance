#pragma once
#ifndef __SERVER__ACTOR__FACTORY_H__
#define __SERVER__ACTOR__FACTORY_H__

#include "engine/actor/factory.h"
#include "server/core/game_object.h"

namespace NSServer {
	namespace NSActor {

		class CFactory
			: public NSEngine::NSActor::CFactory
			, public NSServer::NSCore::CGameObject {
		public:
			static CFactory* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, nlohmann::json& data
			);

			CFactory(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CFactory();

		};
		typedef CFactory* pFactory;

	}
}

#endif // !__SERVER_FACTORY_H__
