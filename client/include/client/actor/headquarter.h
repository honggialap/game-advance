#pragma once
#ifndef __CLIENT__ACTOR__HEADQUARTER_H__
#define __CLIENT__ACTOR__HEADQUARTER_H__

#include "engine/actor/headquarter.h"
#include "client/core/game_object.h"

namespace NSClient {
	namespace NSActor {

		class CHeadquarter
			: public NSEngine::NSActor::CHeadquarter
			, public NSClient::NSCore::CGameObject {
		public:
			static CHeadquarter* Create(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, std::string name
			);

			CHeadquarter(
				NSEngine::NSCore::pGame game
				, NSEngine::NSCore::pWorld world
				, uint32_t id
				, std::string name
			);
			~CHeadquarter();

		};
		typedef CHeadquarter* pHeadquarter;

	}
}

#endif // !__CLIENT__ACTOR__HEADQUARTER_H__
