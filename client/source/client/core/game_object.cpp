#include "client/core/game_object.h"
#include "client/core/game.h"
#include "client/core/world.h"

namespace NSClient {
	namespace NSCore {

		CGameObject::CGameObject(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
		)
			: game_client(static_cast<NSClient::NSCore::pGame>(game))
			, client_world(static_cast<NSClient::NSCore::pWorld>(world)) {
		}

		CGameObject::~CGameObject() {
		}

	}
}
