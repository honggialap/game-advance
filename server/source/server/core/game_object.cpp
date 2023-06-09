#include "server/core/game_object.h"
#include "server/core/game.h"
#include "server/core/world.h"

namespace NSServer {
	namespace NSCore {

		CGameObject::CGameObject(
			NSEngine::NSCore::pGame game
			, NSEngine::NSCore::pWorld world
		)
			: game_server(static_cast<NSServer::NSCore::pGame>(game))
			, server_world(static_cast<NSServer::NSCore::pWorld>(world)) {
		}

		CGameObject::~CGameObject() {
		}

	}
}
