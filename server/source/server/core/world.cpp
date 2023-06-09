#include "server/core/world.h"

namespace NSServer {
	namespace NSCore {

		CWorld::CWorld(NSEngine::NSCore::pGame game)
			: NSEngine::NSCore::CWorld(game)
			, game_server(static_cast<NSServer::NSCore::pGame>(game)) {
		}

		CWorld::~CWorld() {
		}

	}
}

